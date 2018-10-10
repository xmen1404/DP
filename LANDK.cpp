#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define pb push_back
#define int long long
#define ll long long

const int mod = 1e9 + 7;
const int oo = 1e9;
const int N = 2005;

int n, k;
int a[N][N], h[N], L[N], R[N];
int f[N][N], ans;
bool visit[N][N];
struct mask{
    int x1, y1, x2, y2;
}t;

ll get(int x1, int y1, int x2, int y2) { return f[x2][y2] - f[x2][y1 - 1] - f[x1 - 1][y2] + f[x1 - 1][y1 - 1]; }

void solve1()   {
    // cons all the rectangle which have base on the left and on the right
    // row
    for(int i = 1; i <= n; ++i) {
        ll sum = 0ll;
        int las = 0;
        FOR(j, 1, n)    {
            if(visit[i][j]) sum = 0ll, las = j;
            else {
                sum += 1ll * a[i][j];
                if(sum >= k && sum <= 2*k) {
                    cout << las + 1 << ' ' << i << ' ' << j << ' ' << i;
                    exit(0);
                }
            }
        }
        sum = 0ll, las = 0;
        FOR(j, 1, n) {
            if(visit[j][i]) sum = 0ll, las = j;
            else {
                sum += 1ll * a[j][i];
                if(k <= sum && sum <= 2*k) {
                    cout << i << ' ' << las + 1 << ' ' << i << ' ' << j;
                    exit(0);
                }
            }
        }
    }
    // done
    // now if we not have any
}

void solve2()   {
    h[0] = h[n + 1] = -1;
    FOR(i, 1, n) FOR(j, 1, n) f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + a[i][j];
    FOR(i, 1, n)    {
        FOR(j, 1, n)
            if(!visit[i][j]) h[j]++;
            else h[j] = 0;
        stack<int> st;
        st.push(0);
        // left
        FOR(j, 1, n)    {
            while(h[ st.top() ] >= h[j]) st.pop();
            L[j] = st.top() + 1;
            st.push(j);
        }
        while(!st.empty()) st.pop();
        st.push(n + 1);
        for(int j = n; j >= 1; --j) {
            while(h[ st.top() ] >= h[j]) st.pop();
            R[j] = st.top() - 1;
            st.push(j);
        }
        // now we have left and right nad height
        FOR(j, 1, n)    if(h[j] > 0){
            int x1 = i - h[j] + 1, y1 = L[j];
            int x2 = i, y2 = R[j];
            if(ans < get(x1, y1, x2, y2)) {
                ans = get(x1, y1, x2, y2);
                t = {x1, y1, x2, y2};
            }
        }
    }
    if(ans < k) {
        cout << "NIE";
        exit(0);
    } else {
        while(t.x1 < t.x2 && ans > 2ll*k) {
            ans -= get(t.x2, t.y1, t.x2, t.y2);
            t.x2 --;
        }
        while(t.y1 < t.y2 && ans > 2ll*k) {
            ans -= get(t.x1, t.y2, t.x2, t.y2);
            t.y2 --;
        }
        cout << t.y1 << ' ' << t.x1 << ' ' << t.y2 << ' ' << t.x2 << '\n';
    }
}

signed main()
{
    //freopen("test.inp", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> k >> n;

    FOR(i, 1, n) FOR(j, 1, n) {
        cin >> a[i][j];
        if(a[i][j] > 2*k) visit[i][j] = true;
    }
    FOR(i, 1, n) FOR(j, 1, n) {
        if(a[i][j] >= k && a[i][j] <= 2*k){
            cout << j << ' ' << i << ' ' << j << ' ' << i ; return 0;
        }
    }
    solve1();
    solve2();
}
