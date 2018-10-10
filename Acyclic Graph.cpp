#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define pb push_back

const int mod = 1e9 + 7;
const int N = 5e4 + 10;
const int oo = 1e9;

int n, m;
int deg[N], f[N];
bool visit[N];
bitset<N> mask[N];
vector<int> vi[N];

void solve(int u)   {
    visit[u] = true;
    for(int v: vi[u]){
        if(!visit[v]) solve(v);
        mask[u].set(v);
        mask[u] |= mask[v];
    }
    f[u] = mask[u].count();
}

signed main()
{
    //freopen("test.inp", "r", stdin);

}
