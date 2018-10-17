#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define FOR(a, b, c)

const int N = 1e5 + 10;
const int oo = 1e9 + 7;

struct node{
    int len, cnt, link;
    int nex[30];
    void reset()    {
        this->len = this->cnt = this->link = 0;
        for(int i = 0; i <= 26; ++i) this->nex[i] = 0;
    }
};

int n, cnt, curnode;

void inser(int x)   {
    int tmp = curnode;
    // find link
    while(true) {
        if(x - t[tmp].length() >= 1 && s[ x - t[tmp].length() - 1 ] == s[x])
            break;
        tmp = t[tmp].link;
    }
    if(t[tmp].nex[ s[x] - 'a' ] != 0) {
        curnode = tmp;
        cnt[curnode] ++;
        return;
    }

}

signed main()
{
    ios_base::sync_with_stdio(false);
}
