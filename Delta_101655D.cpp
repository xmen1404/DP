#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back

const int N = 1e4 + 10;
const int M = 20;
const int oo = 1e9;
typedef pair<int, int> ii;

int n, m, maxn;
int up[N][25], down[N][25], tmp[N][M], sz[N];
vector<ii> vi[N];

void upd(int &x, int y) { x = min(x, y); }
void Sup(int pre, int u)    {
    up[u][1] = 0;
    sz[u] = 1;
    for(ii v: vi[u]) if(v.fi != pre)    {
        Sup(u, v.fi);
        sz[u] += sz[v.fi];
        for(int i = 1; i <= sz[u]; ++i)
            for(int j = 1; j <= min(i, sz[v.fi]); ++j)
                upd(up[u][i], up[v.fi][i - j] + 2 * v.se + up[u][j]);
    }
}

void Sdown(int pre, int u)  {
    down[u][1] = 0;
    int cnt = 0, ptr = 0, cursz = 0;
    for(ii v: vi[u]) if(v.fi != pre) cnt ++;
    for(int i = 0; i <= cnt; ++i) for(int j = 1; j <= 20; ++j)
        pre[i][j] = suff[i][j] = oo;
    for(ii v: vi[u]) if(v.fi != pre) {
        ptr ++;
        cursz += sz[v.fi];
        for(int i = 1; i <= cursz; ++i) for(int j = 1; j <= sz[v.fi]; ++j)
            upd(pre[ptr][i], up[v.fi][i - j] + 2* v.se + pre[ptr - 1][j]);
    }
    cursz = 0, ptr = cnt + 1;
    for(int cur = vi[u].size() - 1; cur >= 0; --cur)  {
        ii v = vi[u][cur];
        if(v.fi != pre) {
            ptr --;
            cursz += sz[v.fi];
            for(int i = 1; i <= cursz; ++i) for(int j = 1; j <= sz[v.fi]; ++j)
                upd(suff[ptr][i], up[v.fi][i - j] + 2* v.se + suff[ptr + 1][j]);
        }
    }
}

signed main(){
    freopen("test.inp", "r", stdin);
    int t; scanf("%d", &t);
    while(t --) {
        cin >> n >> maxn;
        for(int i = 1; i <= n; ++i) vi[i].clear();
        for(int i = 1; i <= n; ++i) for(int j = 0; j <= M; ++j)
            up[i][j] = oo, down[i][j] = oo;
        for(int i = 1; i < n; ++i) {
            int u, v, c; cin >> u >> v >> c;
            vi[u].pb(ii(v, c));
            vi[v].pb(ii(v, c));
        }
        Sup(1, 1);
        Sdown(1, 1);
        for(int i = 1; i <= n; ++i)
    }
}
