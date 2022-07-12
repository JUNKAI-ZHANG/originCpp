#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct VirtualTree {
    int n = 0, Dfn = 0, Top = 0;
    vector<vector<int>> G, g;
    vector<int> sz, dep, son, top, fa, dfn, stk, vis;

    VirtualTree(int n_) : n(n_) {
        G.resize(n + 1);
        g.resize(n + 1);
        fa.resize(n + 1);
        sz.resize(n + 1);
        dep.resize(n + 1);
        son.resize(n + 1);
        top.resize(n + 1);
        dfn.resize(n + 1);
        stk.resize(n + 1);
    }
    void dfs_1(int x) {
        sz[x] = 1, dep[x] = dep[fa[x]] + 1, dfn[x] = ++Dfn;
        for(int to : G[x]) {
            if(to == fa[x]) continue;
            fa[to] = x;
            dfs_1(to);
            sz[x] += sz[to];
            if(sz[to] > sz[son[x]]) son[x] = to;
        }
    }
    void dfs_2(int x, int Tp) {
        top[x] = Tp;
        if(son[x]) dfs_2(son[x], Tp);
        for(int to : G[x]) {
            if(to == fa[x] || to == son[x]) continue;
            dfs_2(to, to);
        }
    }

    int LCA(int x, int y) {
        while(top[x] != top[y]) {
            if(dep[top[x]] < dep[top[y]]) y = fa[top[y]];
            else x = fa[top[x]];
        }
        return dep[x] < dep[y]? x : y;
    }
    void initTree() {
        for(int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs_1(1);
        dfs_2(1, 1);
    }
    void insert(int u) {
        if(Top == 1) {
            stk[++Top] = u;
            return;
        }
        int lca = LCA(u,stk[Top]);
        if(lca == stk[Top]) return;
        while(Top > 1 && dfn[lca] <= dfn[stk[Top - 1]]) {
            g[stk[Top - 1]].push_back(stk[Top]);
            g[stk[Top]].push_back(stk[Top - 1]);
            vis.push_back(stk[Top - 1]);
            vis.push_back(stk[Top]);
            Top--;
        }
        if(stk[Top] != lca) {
            g[lca].push_back(stk[Top]);
            g[stk[Top]].push_back(lca);
            vis.push_back(lca);
            vis.push_back(stk[Top]);
            stk[Top] = lca;
        }
        stk[++Top] = u;
    }
    void build(vector<int> ve) {
        stk[++Top] = 1;//Ensure VirtualTree exist point 1
        sort(ve.begin(), ve.end(), [&](int aa, int bb) {
            return dfn[aa] < dfn[bb];
        });
        for(int i : ve) insert(i);
        while(--Top) {
            g[stk[Top]].push_back(stk[Top + 1]);
            g[stk[Top + 1]].push_back(stk[Top]);
            vis.push_back(stk[Top + 1]);
            vis.push_back(stk[Top]);
        }
    }
    void clr() {
        for(int i : vis) if(g[i].size()) g[i].clear();
    }
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    VirtualTree vt(n);
    vt.initTree();
    int q;
    cin >> q;
    while(q--) {
        int len, maxDep = 0, root = 1;
        cin >> len;
        vector<int> a(len);
        set<int> st;
        for(int i = 0; i < len; i++) cin >> a[i], st.insert(a[i]);
        vt.build(a);
        for(int i : a) {
            if(vt.dep[i] > maxDep) {
                maxDep = vt.dep[i];
                root = i;
            }
        }
        int cnt = 0, ok = 0;
        function<void(int, int)> dfs = [&](int x, int fa) {
            cout << x << ' ';
            if(st.count(x)) {
                cnt++;
                if(cnt == len) ok = 1;
            }
            for(int to : vt.g[x]) {
                if(to == fa) continue;
                dfs(to, x);
            }
            if(st.count(x)) {
                cnt--;
            }
        };
        dfs(1, 0);
        cout << '\n';
        vt.clr();
        if(ok) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }

    return 0;
}
/*
9
1 3 1
1 5 1
1 7 1
1 9 1
4 5 1
5 6 1
2 9 1
8 9 1
4
3
3 4 6
3
3 4 6
3
3 4 6
3
3 4 6
 */