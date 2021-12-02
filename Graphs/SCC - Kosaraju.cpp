#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
vector<int> g[2][N];
bool used[N];
vector<int> post;
vector<vector<int>> comps;

void add_edge(int u, int v) {
    g[0][u].push_back(v);
    g[1][v].push_back(u);
}

void dfs_inv(int v) {
    used[v] = 1;
    for (int to : g[1][v]) {
        if (!used[to]) {
            dfs_inv(to);
        }
    }
    post.push_back(v);
}

void dfs(int v, vector<int>& comp) {
    used[v] = 1;
    comp.push_back(v);
    for (int to : g[0][v]) {
        if (!used[to]) {
            dfs(to, comp);
        }
    }
}

void Kosaraju(int n) {
    for (int i = 1; i <= n; i++) {
        used[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs_inv(i);
        }
    }
    reverse(post.begin(), post.end());
    for (int i = 1; i <= n; i++) {
        used[i] = 0;
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
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL_ALIKHAN
    freopen("input.txt", "r", stdin);
#endif



#ifdef LOCAL_ALIKHAN
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}