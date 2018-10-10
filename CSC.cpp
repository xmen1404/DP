#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define pb push_back
#define int long long

const int N = 1e5 + 10;
const int mod = 1e9 + 7;
const int oo = 1e10;

int n;
int a[N];

int f(int x)    {
    int cur = 1, maxn = -oo;
    FOR(i, 1, n)    {
        maxn = max(maxn, a[i] - cur);
        cur += x;
    }
    int sum = 0; cur = 1;
    FOR(i, 1, n)    {
        sum += maxn - (a[i] - cur);
        cur += x;
    }
    return sum;
}

int BS()    {
    int l = -1e9, r = 1e9;
    FOR(i, 0, 200)  {
        //cout << l << ' ' << r << '\n';
        int x1 = (l + l + r) / 3;
        int x2 = (l + r + r) / 3;
        if(f(x1) < f(x2)) r = x2;
        else l = x1;
    }
    int sum = 1e18;
    FOR(i, l, r) sum = min(sum, f(i));
    return sum;
}

signed main()
{
    //freopen("test.inp")
    //freopen("rev.inp", "r", stdin);
    //freopen("rev.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    FOR(i, 1, n) cin >> a[i];
    //cout << f(8) << ' ' << f(35) << '\n';
    cout << BS();
}
