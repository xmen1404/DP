#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
typedef pair<int, int> ii;
const int N = 105;
const int mod = 1e9 + 9;
const int oo = 1e9;

int n, maxl, len, m;
int f[100005], dist[N][N], a[100005], mask[100005], ans[100005];
ii  tmp[100005][N];
bool eg[N][N];
string s[N];

void prepare()  {
    FOR(i, 1, n) FOR(j, 1, n) if(i != j) dist[i][j] = oo;
    FOR(i, 1, n) FOR(j, 1, n) {
        int cnt = 0;
        FOR(t, 0, len - 1) if(s[i][t] != s[j][t]) cnt ++;
        if(cnt <= maxl) {
            eg[i][j] = true;
            dist[i][j] = min(dist[i][j], 1);
        }
    }
    // done edge, now we need to find dist[i][j] by using floyd
    FOR(i, 1, n) {
        FOR(u, 1, n) FOR(v, 1, n) dist[u][v] = min(dist[u][v], dist[u][i] + dist[i][v]);
    }
    // now we have dist[u][v] be the min cost to go from u -> v

}

void calc(int st, int en)   {
    if(st == 0) {
        FOR(i, 1, en) ans[i] = a[en];
        return;
    }
    ans[st] = a[st]; ans[en] = a[en];
    int pos = st + 1, cur = a[st];
    while(pos < en) {
        if(eg[cur][ a[en] ]) ans[pos] = cur, pos ++;
        else {
            for(int i = 1; i <= n; ++i) if(eg[cur][i] && dist[ a[st] ][cur] + 1 == dist[a[st]][i] && dist[ a[st] ][i] + dist[i][ a[en] ] == dist[ a[st] ][ a[en] ]){
                ans[pos] = i;
                cur = i;
                break;
            }
            pos ++;
        }
    }
}

signed main()
{
    //freopen("test.inp", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> len >> maxl;
    FOR(i, 1, n) cin >> s[i];
    cin >> m;
    FOR(i, 1, m) cin >> a[i];
    prepare();


    FOR(i, 0, m) f[i] = oo;
    FOR(i, 0, m) FOR(j, 0, n) tmp[i][j] = ii(-1, -1);
    f[1] = 0; tmp[1][ a[1] ] = ii(0, 1);
    FOR(i, 2, m) {
        int cur = a[i];
        f[i] = i - 1; mask[i] = 0;
        if(tmp[i - 1][cur].fi != -1) {
            if(f[i] > tmp[i - 1][cur].fi) f[i] = tmp[i - 1][cur].fi, mask[i] = tmp[i - 1][cur].se;
        }
        FOR(las, 1, n) if(las != cur) {
            int d = dist[cur][las] - 1;
            if(i >= d + 1 && tmp[i - d - 1][las].fi != -1) {
                if(f[i] > tmp[i - d - 1][las].fi + d)
                    f[i] = tmp[i - d - 1][las].fi + d, mask[i] = tmp[i - d - 1][las].se;
            }
        }
        FOR(j, 1, n) if(tmp[i - 1][j].fi != -1) tmp[i][j].fi = tmp[i - 1][j].fi + 1, tmp[i][j].se = tmp[i - 1][j].se;
        if(f[i] < tmp[i][cur].fi || tmp[i][cur].fi == -1) tmp[i][cur] = ii(f[i], i);
        //cout << i << ' ' << f[i] << ' ' << cur << ' ' << tmp[i][cur].fi << '\n';
    }
    int maxn = oo, pos = m;
    FOR(i, 1, m) {
        if(maxn > f[i] + m - i) pos = i, maxn = f[i] + m - i;
    }

    while(pos > 0)  {
        int las = mask[pos];
        calc(las, pos);
        pos = las;
    }
    FOR(i, 1, m) if(ans[i] == 0) ans[i] = ans[i - 1];
    cout << maxn << '\n';
    FOR(i, 1, m) cout << ans[i] << ' ';
    // trace
}
