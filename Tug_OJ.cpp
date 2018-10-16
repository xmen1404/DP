#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define fi first
#define se second
typedef pair<int, int> ii;

const int N = 2e5 + 5;
const int M = 20 * 30000;
const int oo = 1e9;

ii a[N];
int n, maxn, sum, suma, cnt, curval, total, las, nex = 1;
int cost[N], deg[N], f[2][40 * 30005];
bool alive[N];
vector<int> vi[N];
map<int, int> val;

void bad()  { cout << "NO"; exit(0); }
void upd(int &x, int y) { x = min(x, y); }
void addeg(int u, int v) {
    deg[u] ++; deg[v] ++;
    vi[u].pb(v); vi[v].pb(u);
}

void kill(int u)    {
    int u1 = 0, tmp = 0;
    for(int v: vi[u]) if(!alive[v]) {
        u1 = v; tmp ++;
    }
    if(tmp > 1) return;
    if(u1 == 0) bad();
    if(u <= 3*n) curval += cost[u1];
    alive[u] = alive[u1] = 1;
    for(int v: vi[u1]) if(!alive[v])
        kill(v); // :D
}

void dfs(int u, bool spm)   {
    if(spm == 0) suma += cost[u];
    sum += cost[u];
    alive[u] = true;
    int nex = -1;
    for(int v: vi[u]) if(!alive[v]) {
        nex = v; break;
    }
    alive[nex] = true;
    for(int v: vi[nex]) if(!alive[v])
        dfs(v, 1 - spm);
}

signed main() {
    freopen("test.inp", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	scanf("%d%d", &n, &maxn);
    for(int i = 1; i <= 2*n; ++i) {
        int l, r, c; scanf("%d%d%d", &l, &r, &c);
        total += c;
        addeg(i, 2*n + l);
        addeg(3*n + r, i);
        cost[i] = c;
    }

    for(int i = 2*n + 1; i <= 4*n; ++i) if(deg[i] == 1)
        kill(i);
    for(int i = 1; i <= 4*n; ++i) if(!alive[i]) {
        int tmp = 0;
        for(int v: vi[i]) if(!alive[v]) tmp ++;
        if(tmp > 2) bad();
    }
    // now we have all the circle
    for(int i = 1; i <= 2*n; ++i) if(!alive[i]) {
        sum = suma = 0;
        dfs(i, 0);
        curval += min(suma, sum - suma);
        int x = max(suma, sum - suma) - min(suma, sum - suma);
        val[x] ++;
    }
    for(auto it = val.begin(); it != val.end(); ++it)
        a[++cnt] = ii(it->fi, it->se); // :D
    a[0].se = 0;
    //for(int i = 1; i <= n; ++i) cout << a[i].fi << ' ' << a[i].se << '\n';
    //cout << curval << ' ' << total << '\n';
    for(int i = 0; i <= 1; ++i) for(int j = 0; j <= M; ++j) f[i][j] = oo;
    f[las][0] = 0;
    for(int i = 0; i <= cnt; ++i) {
        for(int j = 0; j <= M; ++j) if(f[las][j] <= a[i].se)    {
            if(f[las][j] < a[i].se) upd(f[las][j + a[i].fi], f[las][j] + 1);
            upd(f[nex][j], 0);
        }
        if(i < cnt) {
            swap(las, nex);
            for(int j = 0; j <= M; ++j) f[nex][j] = oo;
        }
    }
    for(int i = 0; i <= M; ++i) if(f[las][i] <= a[cnt].se) {
        if(abs(2*(curval + i) - total) <= maxn)
            return cout << "YES", 0;
    }
     return cout << "NO", 0;
}
