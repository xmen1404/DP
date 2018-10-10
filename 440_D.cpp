#include<bits/stdc++.h>
using namespace std;

#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define fi first
#define se second
#define pb push_back

typedef pair<int, int> ii;

const int N = 405;
const int oo = 1e9;

int n, k;
int dp[N][N], pr[N], eg[N][N];
bool kt[N];
map<ii, int> mask[N];
vector<int> vi[N];
vector<ii> egtmp;

void solve(int pre, int u){
    pr[u] = pre;
    dp[u][1] = 0;
    for(int v: vi[u])   if(v != pre)    {
        solve(u, v);
        for(int i = k; i >= 1; --i) {
            dp[u][i] ++;
            for(int j = 1; j < i; ++j){
                if(dp[u][i] > dp[u][i - j] + dp[v][j])  {
                    mask[i][ii(u, v)] = j;
                    dp[u][i] = dp[u][i - j] + dp[v][j];
                }
            }
        }
    }
}

void trace(int u, int rem)  {
    //cout << u << ' ' << rem << '\n';
    kt[u] = true;
    for(int i = vi[u].size() - 1; i >= 0; --i)  {
        auto v = vi[u][i];
        int l = mask[rem][ii(u, v)];
        if(l){
            trace(v, l);
        }
        rem -= l;
    }
}

signed main()
{
    //freopen("test.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> k;
    FOR(i, 1, n)    {
        FOR(j, 0, k) dp[i][j] = oo;
    }
    FOR(i, 1, n - 1)    {
        int u, v; cin >> u >> v;
        egtmp.pb(ii(u, v));
        eg[u][v] = eg[v][u] = i;
        vi[u].pb(v); vi[v].pb(u);
    }
    solve(1, 1);
    int ans = oo, pos = 0;
    for(int i = 1; i <= n; ++i) {
        int nex = dp[i][k];
        if(i > 1) nex ++;
        if(ans > nex) {
            ans = nex;
            pos = i;
        }
    }
    cout << (pos == 1 ? dp[pos][k] : dp[pos][k] + 1) << '\n';
    trace(pos, k);
    for(int i = 0; i < egtmp.size(); ++i)   {
        if( kt[ egtmp[i].fi ] + kt[ egtmp[i].se ] == 1 )
            cout << i + 1 << ' ';
    }
}
