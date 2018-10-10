#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a=b;a <= c;++a)
#define pb push_back
#define int long long

const int N = 505;
const int mod = 1e9 + 7;
const int oo = 1e9;

struct eg{
    int x1, y1, x2, y2;
}t[N];

int n, sx, sy;
bool visit[N];
bool inpos(eg pos, int x, int y){
    return (pos.x1 <= x && x <= pos.x2 && pos.y1 <= y && y <= pos.y2);
}

bool load(eg x, eg y)   {
    if(y.x1 == y.x2 && x.x1 <= y.x1 && y.x1 <= x.x2 && y.y1 <= x.y1 && x.y2 <= y.y2) return true;
    if(y.y1 == y.y2 && x.y1 <= y.y1 && y.y1 <= x.y2 && y.x1 <= x.x1 && x.x2 <= y.x2) return true;
    return false;
}

bool check(int d)   {
    eg row = {-d, -d, d, d};
    memset(visit, false, sizeof visit);
    FOR(i, 1, n) {
        // row
        FOR(j, 1, n) if(!visit[j])    {
            if(inpos(row, t[j].x1, t[j].y1) || inpos(row, t[j].x2, t[j].y2) || load(row, t[j])){
                visit[j] = true;
                row.x1 = min(row.x1, min(t[j].x1, t[j].x2));
                row.x2 = max(row.x2, max(t[j].x1, t[j].x2));
                row.y2 = max(row.y2, max(t[j].y1, t[j].y2));
                row.y1 = min(row.y1, min(t[j].y1, t[j].y2));
            }
        }
    }
    if(inpos(row, sx, sy)) return true;
    return false;
}

signed main()
{
    //freopen("test.inp", "r", stdin);
    //freopen("bears.in", "r", stdin);
    //freopen("bears.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> sx >> sy >> n;
    FOR(i, 1, n)    {
        cin >> t[i].x1 >> t[i].y1 >> t[i].x2 >> t[i].y2;
    }
    if(max(abs(sx), abs(sy)) <= 1) {
        cout << "0"; return 0;
    }
    int l = 0, r = oo;
    while(r > l)    {
        int mid = (l + r) / 2;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << r;
}
// 10000000000 10000000000
