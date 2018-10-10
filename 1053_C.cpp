#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define pb push_back
#define int long long

const int N = 2e5 + 10;
const int mod = 1e9 + 7;
const int oo = 1e9;

struct num{
    int a, b;
}BIT[5][N];

int n, q;
num a[N], w[N];

void add(num &x, num y) {
    x.a += y.a;
    x.b += y.b;
    x.a += x.b / mod;
    x.b %= mod;
}

void sub(num &x, num y){
    x.a -= y.a;
    x.b -= y.b;
    while(x.b < 0) x.a --, x.b += mod;
}
bool cmp(num x, num y)  {
    if(x.a != y.a) return x.a < y.a;
    return x.b <= y.b;
}
num mul(num x, num y) {
    num res; res.a = (x.a * y.a + x.a * y.b + x.b * y.a);
    res.b = x.b * y.b;
    res.a += res.b / mod;
    res.b %= mod;
    return res;
}

void upd(int base, int pos, num val)   {
    for(int i = pos; i <= n; i += (i & -i))
        add(BIT[base][i], val);
}

num getBIT(int base, int pos)    {
    num res; res.a = res.b = 0;
    for(int i = pos; i >= 1; i -= (i & -i))
        add(res, BIT[base][i]);
    return res;
}

num get(int base, int l, int r){
    num res; res.a = res.b = 0;
    res = getBIT(base, r); sub(res, getBIT(base, l - 1));
    return res;
}

num calc(int l, int r, int mid) {
    // calc the left

    //1 2 6 7 10
    //1 1 1 1 2

    num sum = get(1, l, mid - 1);
    //cout << sum.b << '\n';
    num sumaw = get(2, l, mid - 1);
    //cout << "sumwa=" << sumaw.b << '\n';
    num suff = get(4, (n - mid + 2), n - l + 1);
    //cout << suff.b << ' ' << mul({0, n - mid + 1}, sum).b;
    sub(suff, mul({0, n - mid + 1}, sum));
    //cout << "suff=" << suff.b << '\n';
    sum = mul(sum, a[mid]);
    sub(sum, sumaw); sub(sum, suff);
    //cout << "left=" << sum.b << '\n';
    // calc the right
    num sum1 = get(1, mid + 1, r);
    //cout << "sumw=" << sum1.b << '\n';
    num sumaw1 = get(2, mid + 1, r);
    //cout<< "sumwa=" << sumaw1.b << '\n';
    num suff1 = get(3, mid + 1, r);

    sub(suff1, mul({0, mid}, sum1));
    sum1 = mul(sum1, a[mid]);
    sub(sumaw1, sum1); sub(sumaw1, suff1);
//cout << "right=" << sumaw1.b << '\n';
    add(sum, sumaw1);
    return sum;
}

signed main()
{
// 1 = sum of W
// 2 = sum of aj * wj
// 3 = sum of preffix
// 4 = sum of suffix
    //num x, y; x.a = y.a = 0;
    //x.b = 10; y.b = 150;
    //cout << mul(x, y).b << '\n';
    //return 0;
    //freopen("test.inp", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> q;
    FOR(i, 1, n)    cin >> a[i].b, a[i].a = 0;
    FOR(i, 1, n)    cin >> w[i].b, w[i].a = 0;
    FOR(i, 0, n) FOR(j, 0, 4) BIT[j][i].a = BIT[j][i].b = 0;
    //num x = getBIT(1, 1); cout << x.b << '\n';
    //return 0;
    FOR(i, 1, n)    {
        upd(1, i, w[i]);
        upd(2, i, mul(a[i], w[i]));
        upd(3, i, mul({0, i}, w[i]));
        upd(4, n - i + 1, mul({0, n - i + 1}, w[i]));
    }
    //cout << get(4, 1, 5).b << '\n';

    //return 0;
    //cout << calc(1, 3, 2).b << '\n';
    //return 0;
    while(q --) {
        int x, y; cin >> x >> y;
        if(x < 0)   { // update
            x = -x;
            upd(1, x, {-w[x].a, -w[x].b});
            num tmp = mul(a[x], w[x]);
            upd(2, x, {-tmp.a, -tmp.b});
            tmp = mul({0, x}, w[x]);
            upd(3, x, {-tmp.a, -tmp.b});
            tmp = mul({0, n - x + 1}, w[x]);
            upd(4, n - x + 1, {-tmp.a, -tmp.b});

            w[x] = {0, y};
            upd(1, x, w[x]);
            upd(2, x, mul(a[x], w[x]));
            upd(3, x, mul({0, x}, w[x]));
            upd(4, n - x + 1, mul({0, n - x + 1}, w[x]));
        } else {
            int l = x, r = y;
            for(int i = 1; i <= 60; ++i)    {
                int mid1 = l + (r - l) / 3;
                int mid2 = r - (r - l) / 3;
                if(cmp(calc(x, y, mid1), calc(x, y, mid2))) r = mid2;
                else l = mid1;
            }
            num res = calc(x, y, l);
            FOR(i, l, r) {
                num tmp = calc(x, y, i);
                if(cmp(tmp, res)) res = tmp;
            }
            cout << (res.b + mod * mod) % mod << '\n';
         }
    }
}
