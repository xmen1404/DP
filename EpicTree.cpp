#include<bits/stdc++.h>
using namespace std;

#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define pb push_back
#define fi first
#define se second
#define int long long

typedef pair<int, int> ii;

const int N = 1e5 + 10;
const int MOD = 10009;

int n, ans, chain = 1, cnt;
int chainhead[N], chainid[N], st[N], en[N], inpos[N];
int node[2][4*N], childsum[N], child[N], pr[N], la[2][4*N]; // 0 == child, 1 = pr
vector<int> vi[N];

void dfs(int pre, int u){
    child[u] = 1; pr[u] = pre;
    for(int v: vi[u]) if(v != pre){
        dfs(u, v);
        child[u] += child[v];
    }
    return;
}

void true_val(int base, int i, int l, int r)    {
    if(l > r || !la[base][i]) return;
    if(base == 0) node[base][i] = (node[base][i] + la[base][i] * (childsum[r] - childsum[l - 1]) % MOD) % MOD;
    else node[base][i] = (node[base][i] + la[base][i] * (r - l + 1) % MOD) % MOD;
    if(l != r)  {
        la[base][2*i] = (la[base][2*i] + la[base][i]) % MOD;
        la[base][2*i + 1] = (la[base][2*i + 1] + la[base][i]) % MOD;
    }
    la[base][i] = 0;
    return;
}

void upd(int base, int i, int l, int r, int ql, int qr, int val)  {
    true_val(base, i, l, r);
    if(l > r || ql > r || qr < l) return;
    if(ql <= l && r <= qr)  {
        if(base == 0)
            node[base][i] = (node[base][i] + val * (childsum[r] - childsum[l - 1]) % MOD) % MOD;
        else node[base][i] = (node[base][i] + val * (r - l + 1) % MOD) % MOD;
        if(l != r)  {
            la[base][2*i] = (la[base][2*i] + val) % MOD;
            la[base][2*i + 1] = (la[base][2*i + 1] + val) % MOD;
        }
        return;
    }
    int mid = (l + r) / 2;
    upd(base, 2*i, l, mid, ql, qr, val);
    upd(base, 2*i + 1, mid + 1, r, ql, qr, val);
    node[base][i] = (node[base][2*i] + node[base][2*i + 1]) % MOD;
}

int getm(int base, int i, int l, int r, int ql, int qr) {
    true_val(base, i, l, r);
    if(l > r || ql > r || qr < l) return 0;
    if(ql <= l && r <= qr) return node[base][i];
    int mid = (l + r) / 2;
    return (getm(base, 2*i, l, mid, ql, qr) + getm(base, 2*i + 1, mid + 1, r, ql, qr) ) % MOD;
}

void hld(int u) {
    if(chainhead[chain] == 0) chainhead[chain] = u;
    chainid[u] = chain;
    st[u] = ++cnt; inpos[cnt] = u;

    int bign = -1;
    for(int v: vi[u])   if(v != pr[u]) {
        if(bign == -1 || child[v] > child[bign]) bign = v;
    }
    if(bign != -1) hld(bign);
    for(int v: vi[u]) if(v != pr[u] && v != bign) {
        chain ++; hld(v);
    }
    en[u] = cnt;
    return;
}

void query(int u, int v, int val, bool spm)  {
    while(chainid[u] != chainid[v]) {
        if(chainid[u] < chainid[v]) swap(u, v);
        int head = chainhead[ chainid[u] ];
        if(spm == false)    {
            upd(0, 1, 1, n, st[head], st[u], val);
            upd(1, 1, 1, n, st[head], st[u], val);
        } else ans += getm(1, 1, 1, n, st[head], st[u]), ans %= MOD;
        u = pr[head];
    }

    if(st[u] < st[v]) swap(u, v);
    if(spm == false) {
        upd(0, 1, 1, n, st[v], st[u], val);
        upd(1, 1, 1, n, st[v], st[u], val);
    } else ans += getm(1, 1, 1, n, st[v], st[u]), ans %= MOD;
}

signed main()
{
    //freopen("test.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    FOR(i, 1, n - 1)    {
        int u, v; cin >> u >> v;
        vi[u].pb(v); vi[v].pb(u);
    }
    dfs(1, 1);
    hld(1);
    for(int i = 1; i <= n; ++i) {
        childsum[i] = (child[ inpos[i] ] + childsum[i - 1]);
    }
    //query(5, 11,  2, 0);
    //query(1, 1, 0, true); cout << ans * child[3] << ' ' << getm(0, 1, 1, n, st[6], en[6]) << '\n';


    int q; cin >> q;
    while(q --)     {
        int t; cin >> t;
        if(t == 1)  {
            int u, v, val; cin >> u >> v >> val;
            query(u, v, val, false);
        } else {
            int u; cin >> u;
            int sum = getm(0, 1, 1, n, st[u], en[u]);
            ans = 0ll;
            if(u != 1) query(pr[u], 1, 0, true);
            cout << (ans * child[u] % MOD + sum) % MOD << '\n';
        }
    }
}
