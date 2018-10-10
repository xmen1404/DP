#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)

const int N = 30005;
const int mod = 1e9 + 9;

int n, las = 0, nex = 1, maxn;
int f[2][N];
char s[N];

void add(int &x, int y) { if(x == -1) x = 0; x = (x + y) % mod; }

signed main()
{
    //freopen("test.inp", "r", stdin);
    //freopen("brackets.in", "r", stdin);
    //freopen("brackets.out", "w", stdout);
    scanf("%d", &n);
    FOR(i, 1, n) scanf(" %c", &s[i]);
    f[0][0] = 1;

    FOR(i, 0, n - 1) {
        for(int j = (i % 2); j <= i; j += 2) if(f[las][j] > 0) {
            if(s[i + 1] == ')') {
                if(j > 0) add(f[nex][j - 1], f[las][j]);
            } else {
                if(j > 0) add(f[nex][j - 1], f[las][j]);
                add(f[nex][j + 1], f[las][j]);
            }
        }
        swap(nex, las);
        for(int j = (i % 2); j <= i; j += 2) f[nex][j] = 0;
    }
    printf("%d", f[las][0]);
}
