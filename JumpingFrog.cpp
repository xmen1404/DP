#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define pb push_back

const int N = 2e5 + 10;
const int mod = 1e9 + 7;
const int oo = 1e9;

int n;
int cnt[N], ans[N];
string s;

bool solve(int x)    {
    memset(cnt, 0, sizeof cnt);
    FOR(i, 0, n - 1)    if(s[i] == 'R') {
        cnt[i % x] ++;
    }
    FOR(i, 0, n - 1) if(cnt[i] == n / x)
        return 1;
    return 0;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> s;   n = s.length();
    vector<int> tmp;
    FOR(i, 1, n - 1) tmp.pb(__gcd(n, i));
    sort(tmp.begin(), tmp.end());
    int las = unique(tmp.begin(), tmp.end()) - tmp.begin();
    for(int i = 0; i < las ; ++i) {
        int v = tmp[i];
        //cout << v << '\n';
        ans[v] += solve(v);
    }
    int sum = 0;
    FOR(i, 1, n - 1) sum += ans[__gcd(n, i)];
    cout << sum;
}
