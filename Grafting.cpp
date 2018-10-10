#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define int long long

typedef pair<int, pair<int, int> > pii;

const int N = 105;
const int mod = 1e9 + 7;
const int oo = 1e9;

int n, cnt;
int ndeg[N], deg[N], pr[N];
bool visit[N], ega[N][N], egb[N][N], ta[N][N], tb[N][N];

int calc(int root, int nex) {
    set<pii> st;
    memset(visit, false, sizeof visit);
    ta = ega; tb = egb;

    if(ega[root][nex])  {
        cnt = 0;
        st.insert(pii{0, ii(1, root)});
    } else {
        cnt = 1;
        FOR(i, 1, n) if(ta[root][i])    {
            ndeg[i] --;
            ta[root][i] = ta[i][root] = false;
        }
        ta[root][nex] = ta[nex][root] = true;
        ndeg[nex] ++;
        st.insert(pii{1, ii(1, root)});
    }
    pr[root] = root;
// now we done the problem formally
    while(!st.empty() && (st.begin()->fi == 0 || st.begin()->se.fi == 1))  {
        int u = st.begin()->se.se;
        bool flag = st.begin()->fi;
        visit[u] = true;
        st.erase(st.begin());


    }
    if(st.size() == 0) return cnt;
    return oo;
}

void solve()    {
    cin >> n;
    memset(ega, false, sizeof ega);
    memset(egb, false, sizeof egb);
    FOR(i, 1, n) ega[i][i] = egb[i][i] = true;
    FOR(i, 1, n - 1)    {
        int u, v; cin >> u >> v;
        ega[u][v] = ega[v][u] = true;
        deg[u] ++; deg[v] ++;
    }

    FOR(i, 1, n - 1)    {
        int u, v; cin >> u >> v;
        egb[u][v] = egb[v][u] = true;
    }

    // now we find the cons vertex which will be replace first
    int ans = oo, root = 0;
    FOR(i, 1, n)    {
        if(deg[i] == 1) {
            FOR(j, 1, n) ans = min(ans, calc(i, j));
        }
    }
    if(ans < oo) cout << ans << '\n';
    else cout << "-1\n";
}

signed main()
{
    freopen("test.inp", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t --) solve();
    return 0; // :D
 }
