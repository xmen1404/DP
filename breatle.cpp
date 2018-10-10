#include<bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define pb push_back

const int mod = 1e9 + 7;
const int N = 305;
const int oo = 1e9;

int n, lcnt, rcnt, m;
int a[N], L[N], R[N];
int f[N][N][2];

int solve(int l, int r, bool dir, int cnt) {
    if(l + r == cnt)  return 0;
    if(f[l][r][dir] != -1) return f[l][r][dir];
    int &res = f[l][r][dir]; res = oo;
    if(l < lcnt) {
        int val = (cnt - l - r) * (L[l] - L[l + 1]);
        if(dir) val = (cnt - l - r) * (R[r] - L[l + 1]);
        res = min(res, solve(l + 1, r, 0, cnt) + val);
    }
    if(r < rcnt) {
        int val = (cnt - l - r) * (R[r + 1] - R[r]);
        if(dir == 0) val = (cnt - l - r) * (R[r + 1] - L[l]);
        res = min(res, solve(l, r + 1, 1, cnt) + val);
    }
    return res;
}

signed main(){
    //freopen("test.inp", "r", stdin);
    a[1] = 0;
    scanf("%d%d", &n, &m);
    FOR(i, 1, n) scanf("%d", &a[i + 1]);
    sort(a + 1, a + n + 2);

    int mid = 0;
    FOR(i, 1, n + 1) if(a[i] == 0) mid = i;
    FOR(i, mid, n + 1) R[++rcnt] = a[i];
    for(int i = mid; i >= 1; --i) L[++lcnt] = a[i];

    int res = 0;
    FOR(i, 1, n) {
        memset(f, -1, sizeof f);
        //cout << m * i << ' ' << solve(1, 1, 0, i + 2) << '\n';
        res = max(res, m * i - solve(1, 1, 0, i + 2));
    }
    cout << res;
}
