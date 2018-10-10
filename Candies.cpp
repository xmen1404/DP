#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a=b;a <= c;++a)
#define pb push_back
#define int long long

typedef pair<int, int> ii;

const int N = 1e5 + 10;
const int mod = 1e9 + 7;
const int M = 1e6 + 10;

int n, ans, mask;
int a[105];

signed main()
{
    //freopen("test.inp", "r", stdin);
    //freopen("candies.in", "r", stdin);
    //freopen("candies.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    FOR(i, 1, n) cin >> a[i];
    bitset<M> dp;
    a[0] = 1e9;
    FOR(cur, 1, n)    {
        dp.reset();
        dp.set(0);
        FOR(i, 1, n)   if(i != cur) {
            dp = (dp | (dp << a[i]));
        }
        //cout << cur << ' ' << dp.count() - 1 << '\n';
        if(ans < (int)dp.count() - 1) {
            ans = (int)dp.count() - 1;
            mask = cur;
        } else if(a[mask] > a[cur] && ans == (int)dp.count() - 1) mask = cur; // sai!!
    }
    dp.reset();
    dp.set(0);
    for(int i = 1; i <= n; ++i) if(i != mask)
        dp = (dp | (dp << a[i]));
    for(int i = 1; i <= n; ++i) if(i != mask)
        dp = (dp | (dp >> a[i]));
    //FOR(i, 1, 9) cout << i << ' ' << dp.test(i) << '\n';
    for(int i = 1; i <= 1e6; ++i) if(dp.test(i) == false){
        cout << a[mask] << ' ' << i;
        return 0;
    }
}
