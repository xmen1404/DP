#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define pb push_back

const int mod = 1e9 + 7;
const int N = 20;
const int oo = 1e9;

int n;
bool f[N][(1 << 17)];
string s;

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> s; n = s.length();
    int val = 0;
    FOR(i, 0, n - 1) val = val * 2 + s[i] - '0';
    f[0][(1 << n) - 1] = 1;

    FOR(i, 0, n - 1) FOR(mask, 0, (1 << n) - 1)   if(f[i][mask] > 0) {
        //cout << i << ' ' << mask << '\n';
        int cur = (1 << (i + 1)) - 1;
        f[i + 1][mask] = 1;
        for(int t = 1; t <= n; ++t)  {
            int st = t - (i + 1);
            if(st < 0) f[i + 1][mask ^ (cur >> (-st))] = 1;
            else f[i + 1][mask ^ (cur << st)] = 1;
        }
    }

    FOR(i, 0, n) if(f[i][val]) {
        cout << i; return 0;
    }
}
