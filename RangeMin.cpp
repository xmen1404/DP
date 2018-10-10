#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b;a <= c; ++a)
#define pb push_back
#define int long long

const int N = 2005;
const int mod = 1e9 + 7;
const int oo = 1e15;

typedef pair< pair<int, int>, pair<int, int> > pii;

int n, k, q, ans;
int a[N], b[N];
bool visit[N];
priority_queue<int, vector<int>, greater<int> > pq;


int solve() {
    while(!pq.empty()) pq.pop();
    int cur = -oo;
    int l = 1, r = l;
    while(l <= n)   {
        while(visit[l]) l ++;
        r = l;
        while(r < n && visit[r + 1] == false) r ++;

        if(r >= l && r - l + 1 >= k && r <= n) {
            vector<int> tmp;
            FOR(i, l, r) tmp.pb(a[i]);
            sort(tmp.begin(), tmp.end());
            for(int i = 0; i < (r - l + 1 - k + 1); ++i) pq.push(tmp[i]);
        }
        l = r + 1;
    }
    FOR(i, 1, q)    {
        if(pq.empty()) return oo;
        cur = max(cur, pq.top());
        pq.pop();
    }
    return cur;
}

signed main()
{
    //freopen("test.inp", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> k >> q;
    FOR(i, 1, n) {
        cin >> a[i];
    }

    //cout << solve() << '\n';
    //return 0;
    // done
    ans = oo;
    FOR(i, 1, n)    {
        memset(visit, false, sizeof visit);
        FOR(j, 1, n) if(a[j] < a[i]) visit[j] = true;
        int cur = solve();
        //cout << a[i] << ' ' << cur << '\n';
        ans = min(ans, cur - a[i]);
    }
    cout << ans;
}
