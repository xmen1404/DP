#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define int long long

const int N = 105;
const int mod = 1e9 + 7;

int n, x;
int pw[N], dp[N][N][N];
string s;
void add(int &x, int y) {
    x = (x + y) % mod;
}
int solve(int l, int r, int pos)    {
    //cout << l << ' ' << r << ' ' << pos << '\n';
    if(l > r) return 1ll;
    if(pos < 0) return 0;
    if(pos == 0) return (l == r && s[l] == '0');
    if(pos == 1) return (l == r && s[l] == '1');

    int &sum = dp[l][r][pos];
    if(sum != -1) return sum;

    sum = 0;
    add(sum, solve(l, r, pos - 2) * ((l == 0) ? pw[pos - 1] : 1));
    add(sum, solve(l, r, pos - 1) * ((r == n - 1) ? pw[pos - 2] : 1));
    for(int mid = l; mid < r; ++mid)   {
        int cur = 1ll * solve(l, mid, pos - 1) * solve(mid + 1, r, pos - 2);
        sum = (sum + cur) % mod;
    }
    //cout << l << ' ' << r << ' ' << pos << ' ' << sum << '\n';
    return sum;
}

signed main()
{
    // idea of this problem is :
    // we increase the value of ans when s ocurce each time in f[x]
    // then we have a dp solution:
    // let f[l][r][k] be the sum of value when we cons s in the substring [l->r]
    // then we can optain the value by mid [l->r-1]
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> x >> s;

    memset(dp, -1, sizeof dp);

    pw[0] = pw[1] = 2;
    FOR(i, 2, x + 1) pw[i] = 1ll * pw[i - 1] * pw[i - 2] % mod;
    cout << solve(0, n - 1, x); // done

    return 0;
 }
