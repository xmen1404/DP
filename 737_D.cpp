#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define pb push_back

const int mod = 1e9 + 7;
const int N = 4e3 + 10;
const int oo = 1e9;

int n;
int dp[N][100][100][2], a[N];

int solve(int l, int diff, int pre, bool turn)   {
    int r = n - (l - diff) + 1;
    // now we have the lastest right possition
    //cout << l << ' ' << r << '\n';
    if(!turn) diff += 80;
    int &res = dp[l][diff][pre][turn];
    if(res != -1) return res;
    if(pre > r - l - 1) return 0;
    if(!turn) diff -= 80;
    if(!turn)   {
        // now is turn of Igor
        //res = -1e9;
        res = solve(l + pre, diff + pre, pre, 1 - turn) + a[l + pre] - a[l];
        if(r - l - 1 >= pre + 1) res = max(res, solve(l + pre + 1, diff + pre + 1, pre + 1, 1 - turn) + a[l + pre + 1] - a[l]);
    } else {
        //res = 1e9;
        res = solve(l, diff - pre, pre, 1 - turn) - (a[r - 1] - a[r - pre - 1]);
        if(r - l - 1 >= pre + 1) res = min(res, solve(l, diff - pre - 1, pre + 1, 1 - turn) - (a[r - 1] - a[r - pre - 2]));
    }
    return res;
}

signed main()
{
    //freopen("test.inp", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    FOR(i, 1, n) cin >> a[i], a[i] += a[i - 1];

    memset(dp, -1, sizeof dp);
    cout << max(solve(1, 1, 1, 1) + a[1], solve(2, 2, 2, 1) + a[2]);
}
