#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void merge(map<int, int>&a, const map<int, int>& b) {
    for(const auto&[x, y] : b) {
        a[x] += y;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> leaf, pa(n + 1, 0), cnt(n + 1, 0);
    function<void(int, int, int)> dfs = [&](int x, int fa, int dep) {
        int ok = 0;
        pa[x] = fa;
        for(int to : g[x]) {
            if(to == fa) continue;
            ok = 1;
            dfs(to, x, dep + 1);
        }
        if(ok == 0) {
            leaf.push_back(x);
            cnt[x]++;
        }
    };
    dfs(1, 0, 0);
    if(n == 1) return cout << 0 << '\n' , 0;
    for(int ans = 1; ans <= n; ans++) {
        queue<int> q;
        vector<int> vis(n + 1);
        for(int i : leaf) {
            q.push(i);
            vis[i] = 1;
        }
        while(q.size()) {
            int x = q.front();
            q.pop();
            if(x != 1) vis[x] = 0;
            if(pa[x] && cnt[x]) {
                cnt[x]--;
                cnt[pa[x]]++;
            }
            else if(cnt[x] == 0 && vis[pa[x]] == 0) {
                q.push(pa[x]);
                vis[pa[x]] = 1;
            }
        }
        if(cnt[1] == leaf.size()) {
            return cout << ans << '\n', 0;
        }
    }

    return 0;
}
/*
 6
 1 2
 1 3
 2 4
 2 5
 5 6

 ans = 3

 7
1 2
1 3
2 4
2 5
3 6
3 7

 ans = 3

 10
1 2
1 3
2 4
2 5
4 6
4 7
4 8
6 9
6 10

 ans = 6
 */