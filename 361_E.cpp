#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b;a <= c; ++a)
#define pb push_back
#define int long long

const int N = 2005;
const int MOD = 1e9 + 7;
const int oo = 1e9;

typedef pair<int, int> ii;

int n, k;
int a[N], dp[N][N], sum[N][N];
string s;

void add(int &x, int y) { x = (x + y) % MOD; }
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> k;
    cin >> s;
    sum[0][0] = dp[0][0] = 1;
    FOR(i, 1, n)    {
        FOR(j, 0, k)    {
            add(sum[i][j], sum[i - 1][j] * (s[i - 1] - 'a' + 1));
            for(int p = i; p >= 1; --p) {
                int cur = (i - p + 1) * (n - i + 1);
                if(cur > j) break;
                add(sum[i][j], 1ll * dp[p - 1][j - cur] * ('z' - s[i - 1]));
            }
            //cout << i << ' ' << j << ' ' << sum[i][j] << '\n';
            dp[i][j] = (sum[i][j] - sum[i - 1][j] + 1ll * MOD * MOD) % MOD;
        }
    }
    cout << sum[n][k];
}

