#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a=b;a <= c;++a)
#define pb push_back
#define int long long

const int N = 1e5 + 10;
const int mod = 1e9 + 7;
const int oo = 1e9;

int n;
int f[40][11][11][2];
void add(int &x, int y)  { x = (x + y); }
int solve(string maxn, int st) {
    //cout << st << '\n';
    memset(f, 0ll, sizeof f);
    f[0][0][0][0] = 1ll;
    FOR(i, 0, 18) FOR(las2, 0, 10) FOR(las1, 0, 10) {
        if(f[i][las2][las1][0]) {
            int h = maxn[i] - '0';
            FOR(t, 0, h)    if((i <= st) || (i == st + 1 && t != las1) || (t != las1 && t != las2))    {
                bool flag = 1;
                if(t == h) flag = 0;
                if(i == st && t == 0) {
                    add(f[i + 1][las1][10][flag], f[i][las2][las1][0]);
                    continue;
                }
                if(las1 == 10)  {
                    if(t == 0) add(f[i + 1][las1][10][flag], f[i][las2][las1][0]);
                    else add(f[i + 1][las1][t][flag], f[i][las2][las1][0]);
                } else add(f[i + 1][las1][t][flag], f[i][las2][las1][0]);
            }
        }
        if(f[i][las2][las1][1]) {
            //cout << i << ' ' << las2 << ' ' << las1 << ' ' << f[i][las2][las1][1] << '\n';
            FOR(t, 0, 9)    if((i <= st) || (i == st + 1 && t != las1) || (t != las1 && t != las2))    {
                if(i == st && t == 0) {
                    add(f[i + 1][las1][10][1], f[i][las2][las1][1]);
                    continue;
                }
                if(las1 == 10)  {
                    if(t == 0) add(f[i + 1][las1][10][1], f[i][las2][las1][1]);
                    else add(f[i + 1][las1][t][1], f[i][las2][las1][1]);
                } else add(f[i + 1][las1][t][1], f[i][las2][las1][1]);
            }
        }
    }
    // we need f[18][las1][las2][0]
    int sum = 0ll;
    FOR(i, 0, 10) FOR(j, 0, 10) add(sum, f[19][i][j][0]), add(sum, f[19][i][j][1]);
    return sum;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int l, r;   cin >> l >> r; l --;
    string a = "", b = "";

    while(l > 0)    a = char(l % 10 + 48) + a, l /= 10;
    int sa = 19 * 1ll - a.length();
    while(a.length() < 19) a = "0" + a;

    while(r > 0)    b = char(r % 10 + 48) + b, r /= 10;
    int sb = 19 * 1ll - b.length();
    while(b.length() < 19) b = "0" + b;
//cout << a << ' ' <<sa << ' ' << b << ' ' << sb << ' ' << solve(b, sb)  << '\n' ;
    if(l < 0) cout << solve(b, sb);
    else cout << solve(b, sb) - solve(a, sa);// :D
}
// 10000000000 10000000000
