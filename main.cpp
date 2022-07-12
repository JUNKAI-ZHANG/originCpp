#include <iostream>
#include <cstdio>
#include <stack>
#include <sstream>
#include <limits.h>
#include <vector>
#include <map>
#include <cstring>
#include <deque>
#include <cmath>
#include <iomanip>
#include <queue>
#include <algorithm>
#include <set>
#define mid ((l + r) >> 1)
#define Lson rt << 1, l , mid
#define Rson rt << 1|1, mid + 1, r
#define ms(a,al) memset(a,al,sizeof(a))
#define log2(a) log(a)/log(2)
#define _for(i,a,b) for( int i = (a); i < (b); ++i)
#define _rep(i,a,b) for( int i = (a); i <= (b); ++i)
#define for_(i,a,b) for( int i = (a); i >= (b); -- i)
#define rep_(i,a,b) for( int i = (a); i > (b); -- i)
#define lowbit(x) ((-x) & x)
#define IOS std::ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define INF 0x3f3f3f3f
#define LLF 0x3f3f3f3f3f3f3f3f
#define hash Hash
#define next Next
#define count Count
#define pb push_back
#define f first
#define s second
using namespace std;
const int N = 1e6+10, mod = 1e9 + 9;
const long double eps = 1e-5;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef pair<double,double> PDD;
template<typename T> void read(T &x)
{
    x = 0;char ch = getchar();ll f = 1;
    while(!isdigit(ch)){if(ch == '-')f*=-1;ch=getchar();}
    while(isdigit(ch)){x = x*10+ch-48;ch=getchar();}x*=f;
}
template<typename T, typename... Args> void read(T &first, Args& ... args)
{
    read(first);
    read(args...);
}
int n, p;
int str[N], top;
int f[N][30];
int head[N], cnt;
ll mi[N];
int dep[N], dfn[N], idx;
int q[N];
vector<int> v[250010];
struct node {
    int to, next, w;
} e[N];
inline void dfs(int u, int fa)
{
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    dfn[u] =  ++ idx;
    for(int i = head[u]; ~i; i = e[i].next)
    {
        int v = e[i].to;
        if(v == fa) continue;
        mi[v] = min((ll)e[i].w,mi[u]);
        dfs(v,u);
    }
}

inline void LCAinit()
{
    dfs(1,0);
    for(int j = 0; 1 << (j + 1) < n; ++ j)
        for(int i = 1; i <= n; ++ i)
            if(!f[i][j]) f[i][j + 1] = 0;
            else f[i][j + 1] = f[f[i][j]][j];
}

inline int LCA(int u, int v)
{
    if(dep[u] < dep[v]) swap(u,v);
    int delta = dep[u] - dep[v];
    for(int i = 0; (delta >> i) > 0; ++ i)
        if(delta >> i & 1) u = f[u][i];

    if(u == v) return u;
    for(int i = log2(n); i >= 0; -- i)
        if(f[u][i] != f[v][i])
            u = f[u][i], v = f[v][i];
    return f[u][0];
}

inline void add(int from, int to, int w)
{
    e[cnt] = {to,head[from],w};
    head[from] = cnt ++;
}

inline void add(int x,int y)
{
    v[x].push_back(y);
}

inline bool cmp(int a, int b)
{
    return dfn[a] < dfn[b];
}

inline void insert(int u)
{
    if(top == 1) {str[++ top] = u; return;}
    int lca = LCA(u,str[top]);
    if(lca == str[top]) return;
    while(top > 1 && dfn[lca] <= dfn[str[top - 1]])
    {
        add(str[top - 1], str[top]);
        top --;
    }
    if(str[top] != lca) add(lca,str[top]), str[top] = lca;
    str[++ top] = u;
}

inline ll dp(int x)
{
    cout << x << ' ';
    if(v[x].size()==0) return mi[x];
    ll ans=0;
    for(int i=0;i<v[x].size();i++){
        ans+=dp(v[x][i]);
    }
    v[x].clear();
    return min(ans,mi[x]);
}

int main()
{
    ms(head,-1);
    ms(mi,LLF);
    read(n);
    for(int i = 0; i < n - 1; ++ i)
    {
        int l , r , w;
        read(l,r,w);
        add(l,r, w);
        add(r,l, w);
    }
    LCAinit();
    int m;
    read(m);
    while(m --)
    {
        int num;
        read(num);
        for(int i = 0; i < num; ++ i)
            read(q[i]);
        sort(q,q+num,cmp);
        str[++ top] = 1;
        for(int i = 0; i < num; ++ i) insert(q[i]);
        while(--top) add(str[top],str[top + 1]);
        dp(1);
        cout << endl;
    }
    return 0;
}
/*
5
1 2 1
2 3 1
2 4 1
4 5 1
1
3
1 3 5


5
1 2 1
3 2 1
2 4 1
5 2 1
4
2
3 1
3
3 4 5
3
2 3 5
1
1


 */
