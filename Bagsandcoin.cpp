#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define pb push_back

const int mod = 1e9 + 7;
const int N = 7e4 + 10;
const int oo = 1e9;
typedef pair<int, int> ii;

int n, s, maxn;
int a[N], pos[N];
vector<int> ans[N];
bool trace[N];
void bad() { cout << "-1"; exit(0); }
signed main()
{
    //freopen("test.inp", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> s;
    FOR(i, 1, n)    {
        cin >> a[i];
        if(a[i] > a[maxn]) maxn = i;
    }

    if(s < a[maxn]) bad();
    s -= a[maxn]; trace[maxn] = true;

    bitset<N> f[2];
    int las = 0, nex = 1;
    f[las].reset(); f[nex].reset();
    f[las].set(0);

    FOR(i, 1, n)    {
        if(i == maxn) continue;
        f[nex] = (f[las] | (f[las] << a[i]));
        bitset<N> cur = (f[las] ^ f[nex]);
        for(int j = cur._Find_first(); j < N; j = cur._Find_next(j))
            pos[j] = i;
        swap(las, nex);
    }
    if(f[las].test(s) == 0) bad();

    int cur = s;
    while(cur > 0)  {
        trace[ pos[cur] ] = true;
        cur -= a[pos[cur] ];
    }
    set<ii> child, pr;
    FOR(i, 1, n)    {
        if(!trace[i]) child.insert(ii(a[i], i));
        else pr.insert(ii(a[i], i));
    }

    while(child.size() > 0) {
        while(pr.begin()->fi < child.begin()->fi) pr.erase(pr.begin());
        ii cur = {pr.begin()->fi, pr.begin()->se};
        pr.erase(pr.begin());
        auto pos = child.lower_bound(ii(cur.fi + 1, 0));
        pos --;
        ans[cur.se].pb(pos->se);
        cur.fi -= pos->fi;
        if(cur.fi) pr.insert(cur);
        if(pos->fi) pr.insert((*pos));
        child.erase(pos);
    }
    FOR(i, 1, n)    {
        int rem = a[i];
        for(int v: ans[i]) rem -= a[v];
        cout << rem << ' ';
        cout << ans[i].size() << ' ';
        for(int v: ans[i]) cout << v << ' '; cout << '\n';
    }
    // :D
    return 0;
}

