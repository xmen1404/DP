#include<bits/stdc++.h>
using namespace std;

#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define pb push_back
#define fi first
#define se second
#define int long long

const int N = 1e5 + 10;
const int oo = 1e9;
const int MOD = 1e9 + 7;

int n, maxn;
int color[N], dp[N][2];
vector<int> vi[N];

void solve(int pre, int u){
    for(int v: vi[u])   if(v != pre)    {
        solve(u, v);
    }
    if(color[u] == 1)   {
        int tmp1 = 1ll, tmp2 = 0ll;
        dp[u][0] = 0ll;
        for(int v: vi[u])   if(v != pre)    {
            tmp1 = (1ll * tmp1 * dp[v][0] % MOD + tmp1 * dp[v][1] % MOD) % MOD;
        }
        dp[u][1] = tmp1;

    } else {
        // calc the dp[u][1]
        int tmp1 = 1ll, tmp2 = 0ll;
        for(int v: vi[u]) if(v != pre) {
            tmp2 = (tmp2 * dp[v][0] % MOD + tmp2 * dp[v][1] % MOD + tmp1 * dp[v][1] % MOD) % MOD;
            tmp1 = (tmp1 * dp[v][0] % MOD + tmp1 * dp[v][1] % MOD) % MOD;
        }
        dp[u][1] = tmp2;
        dp[u][0] = tmp1;
        // calc the dp[u][0]
    }
}
signed main()
{
    //freopen("test.txt", "r", stdin);
    // let dp[i][1] be the way to slit the sob tree of u and rem contain a black node
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // let dp[i][j] be the nums to slit the ith tree and left j black node
    cin >> n;
    FOR(i, 2, n)    {
        int x; cin >> x; x++;
        vi[i].pb(x); vi[x].pb(i);
    }
    FOR(i, 1, n) cin >> color[i];
    solve(1, 1);
    //cout << dp[2][1] << ' ' << dp[2][0] << '\n';
    cout << dp[1][1];
}
