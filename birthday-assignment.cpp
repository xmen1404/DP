#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int  a = b; a <= c; ++a)
#define pb push_back
#define int long long

typedef pair<int, int> ii;

const int N = 4e3 + 10;
const int mod = 1e9 + 7;
const int oo = 1e9;

int n, m;
int f[N][N], pre[N][N], suff[N][N], sz[N], g[N][N];
int fac[N], facw[N];
vector<ii> vi[N];

void add(int &x, int y) { x = (x + y % mod + 1ll * mod * mod) % mod; }
int pw(int x, int y)    {
    int res = 1ll;
    while(y)    {
        if(y % 2) res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

void prepare()  {
    fac[0] = 1;
    for(int i = 1; i <= 2000; ++i) fac[i] = fac[i - 1] * i % mod;
    for(int i = 0; i <= 2000; ++i) facw[i] = pw(fac[i], mod - 2);
}

int ckn(int k, int n)   {
    if(k > n) return 0;
    int res = fac[n];
    res = res * facw[n - k] % mod * facw[k] % mod;
    return res; // :D done
}

void solve(int pr, int u)  {
    for(ii v: vi[u]) if(v.fi != pr)
        solve(u, v.fi);
    sz[u] = 1; int cnt = 0;
    g[0][1] = 1;
    for(ii v: vi[u]) if(v.fi != pr)    {
        cnt ++;
        for(int i = 0; i <= sz[u] + sz[v.fi]; ++i) g[cnt][i] = 0;
        if(v.se == 1) {
            // v go first
            for(int i = 0; i < sz[u]; ++i) for(int j = 1; j <= sz[v.fi]; ++j){
                int val = g[cnt - 1][i + 1] * pre[v.fi][j] % mod * ckn(j, j + i) % mod * ckn(sz[v.fi] - j, sz[v.fi] - j + sz[u] - i - 1) % mod;
                add(g[cnt][i + j + 1], val);
            }
        } else {
            // u go first
            for(int i = 0; i < sz[u]; ++i) for(int j = 0; j < sz[v.fi]; ++j) {
                int val = g[cnt - 1][i + 1] * suff[v.fi][j + 1] % mod * ckn(i, i + j) % mod * ckn(sz[v.fi] - j, sz[v.fi] - j + sz[u] - i - 1);
                add(g[cnt][i + j +1], val);
            }
        }
        sz[u] += sz[v.fi];
    }
    for(int i = 0; i <= sz[u]; ++i) f[u][i] = g[cnt][i];

    pre[u][0] = f[u][0];
    for(int i = 1; i < N; ++i) pre[u][i] = (pre[u][i - 1] + f[u][i]) % mod;
    for(int i = n; i >= 1; --i) suff[u][i] = (suff[u][i + 1] + f[u][i]) % mod;
    // done
}

int ckn2(int k, int n)  {
    if(k > n) return 0;
    int res = facw[k];
    for(int i = n - k + 1; i <= n; ++i) res = res * i % mod;
    return res;
}

signed main()
{
    //freopen("test.inp", "r", stdin);
    // the mistake in this pro is I used the g[i][j] in wrong way because it's a globe array then we need to calc all the chilrentbefore calc the parent with this array
    // It take me 2h to debug
    // this show that i will fall the 1st exam if this kind of mistake continues!
    // wkingfor APIO
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    prepare();
    //cout << ckn(1, 1); return 0;
    int t; cin >> t;
    while(t --) {
        cin >> n >> m;
        FOR(i, 1, n) vi[i].clear();
        FOR(i, 0, n + 10) FOR(j, 0, n + 10) f[i][j] = pre[i][j] = suff[i][j] = g[i][j] = 0;

        for(int i = 1; i < n; ++i) {
            int u, v; cin >> u >> v;
            vi[u].pb(ii(v, 1));
            vi[v].pb(ii(u, 0));
        }

        solve(1, 1);
        //cout << suff[3][1] << '\n';
        //continue;
        int ans = 0;
        for(int i = 1; i <= n; ++i) add(ans, f[1][i]);
        ans = ans * ckn2(n, m) % mod;
        cout << ans << '\n';
    }
}
/*
3 2
1 1
3 2
*/
