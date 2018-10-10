#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define pb push_back

const int N = 205;
const int mod = 1e9 + 7;
const int oo = 1e9;

int n;
int a[N][N];

signed main()
{
    //freopen("rev.inp", "r", stdin);
    //freopen("rev.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    FOR(i, 1, 2 * n) FOR(j, 1, 2*n) {
        cin >> a[i][j];
    }
    int sum = 0;
    FOR(i, 1, n) FOR(j, 1, n)   {
        int t1 = max(a[i][j], a[i][2*n - j + 1]);
        int t2 = max(a[2*n - i + 1][j], a[2*n - i + 1][2*n - j + 1]);
        sum += max(t1, t2);
    }
    cout << sum;
}
