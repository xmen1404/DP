#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b;a <= c; ++a)
#define pb push_back
#define int long long

const int mod = 1e9 + 7;
const int N = 1e5 + 10;
const int oo = 1e9;

int n;
int a[N][3], f[N][3][2];

void add(int &x, int y) { x = max(x, y); }

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // let f[i][cnt][flag] be the max cost when we cons the ith elements and the nums of val of it is cnt and is it appear earlier than the last one :D
    // the f[i][cnt][flag] = max(f[i - 1][cnt'][flag]) if cnt' = flag + flag';
    cin >> n;
    FOR(i, 1, n) cin >> a[i][0];
    FOR(i, 1, n) cin >> a[i][1];
    FOR(i, 1, n) cin >> a[i][2];

    if(n == 1) {
        cout << a[1][0]; return 0;
    }

    f[1][0][0] = a[1][0];
    f[1][1][0] = a[1][1];
    FOR(i, 2, n)    {
        // cnt la so thang awn truoc
        // cnt = 0
        FOR(t, 0, 2) FOR(fa, 0, 1) {
            // t la so duong di vao
            // 0 i - 1 <= i
            int val = ((i == 2) ? 1 : 2);
            if(fa == val - t) add(f[i][0][1], f[i - 1][t][fa] + a[i][0]);
            // 1
            FOR(t1, 0, 1) if(t1 + fa == val - t)
                add(f[i][1][1 - t1], f[i - 1][t][fa] + a[i][1]);
            // 2 di ra
            if(fa + 1 == val - t) add(f[i][2][0], f[i - 1][t][fa] + a[i][2]);
        }
    }
    int ans = 0;
    FOR(i, 0, 1) FOR(j, 0, 1) if(1 - i == j)
        ans = max(ans, f[n][i][j]);
    cout << ans;
}
