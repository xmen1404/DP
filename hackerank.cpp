#include<bits/stdc++.h>
using namespace std;

#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define fi first
#define se second
#define pb push_back
#define int long long

const int N = 4e5 + 10;
const int oo = 1e9;

int cnt = 1, n, las = 0ll;
int pos[N][30], f[N][30], a[N];

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    FOR(i, 1, N - 1) FOR(j, 0, 20) pos[i][j] = -1, f[i][j] = oo;
    pos[1][0] = 1; f[1][0] = 0;

    int t; cin >> t;
    while(t --)     {
        int ty; cin >> ty;
        if(ty == 1) {
            int R, W; cin >> R >> W;
            R ^= las; W ^= las;
            cnt ++; a[cnt] = W;

            for(int i = 20; i >= 0; --i) if(pos[R][i] != -1 && a[ pos[R][i] ] < W){
                R = pos[R][i];
                if(pos[R][1] != -1 && a[ pos[R][1] ] < W) R = pos[R][1];
            }
            if(a[R] < W) R = pos[R][1];

            pos[cnt][0] = cnt;
            pos[cnt][1] = R;

            for(int i = 2; i <= 20; ++i) if(pos[cnt][i - 1] != -1 && pos[ pos[cnt][i - 1] ][1] != -1)
                pos[cnt][i] = pos[pos[pos[cnt][i - 1]][1]][i - 1];
            f[cnt][0] = W;
            for(int i = 1; i <= 20; ++i)    if(pos[cnt][i - 1] != -1 && pos[ pos[cnt][i - 1] ][1] != -1)
                f[cnt][i] = f[cnt][i - 1] + f[pos[ pos[cnt][i - 1] ][1]][i - 1];
        } else {
            int st, maxn; cin >> st >> maxn;
            st ^= las, maxn ^= las;

            int ans = 0ll;
            for(int i = 20; i >= 0; --i)    {
                if(pos[st][i] != -1 && f[st][i] <= maxn)    {
                    ans += (1ll << i);
                    maxn -= f[st][i];
                    st = pos[ pos[st][i] ][1];
                    if(st == -1) break;
                }
            }
            las = ans;
            cout << ans << '\n';
        }
    }
}
