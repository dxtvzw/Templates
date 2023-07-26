#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Kosaraju {
    const int n;
    vector<vector<int>> g[2];
    vector<bool> used;
    vector<int> post;
    vector<vector<int>> comps;
    Kosaraju(int _n) : n(_n) {
        g[0].resize(n + 1);
        g[1].resize(n + 1);
        used.resize(n + 1, false);
    }
    void add_edge(int u, int v) {
        g[0][u].push_back(v);
        g[1][v].push_back(u);
    }
    void dfs_inv(int v) {
        used[v] = true;
        for (int to : g[1][v]) {
            if (!used[to]) {
                dfs_inv(to);
            }
        }
        post.push_back(v);
    }
    void dfs(int v, vector<int>& comp) {
        used[v] = true;
        comp.push_back(v);
        for (int to: g[0][v]) {
            if (!used[to]) {
                dfs(to, comp);
            }
        }
    }
    const vector<vector<int>>& find_scc() {
        for (int i = 1; i <= n; i++) {
            used[i] = false;
        }
        for (int i = 1; i <= n; i++) {
            if (!used[i]) {
                dfs_inv(i);
            }
        }
        reverse(post.begin(), post.end());
        for (int i = 1; i <= n; i++) {
            used[i] = false;
        }
        for (int v : post) {
            if (!used[v]) {
                vector<int> comp;
                dfs(v, comp);
                comps.push_back(comp);
            }
        }
        reverse(comps.begin(), comps.end());
        // edges go from left to right
        return comps;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif



#ifdef LOCAL
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
}