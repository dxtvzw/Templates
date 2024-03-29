#include <bits/stdc++.h>

using namespace std;

struct union_enumerate {
    static const int N = 1e6 + 10;
    int next[N];
    bool used[N];
    union_enumerate() = default;
    void init(int n) {
        iota(next + 1, next + n + 1, 1);
    }
    vector<int> enumerate(int v) const {
        vector<int> res;
        int u = v;
        do {
            res.push_back(u);
            u = next[u];
        } while (u != v);
        return res;
    }
    vector<vector<int>> get_all(int n) {
        vector<vector<int>> res;
        for (int i = 1; i <= n; i++) {
            if (!used[i]) {
                vector<int> cur = enumerate(i);
                for (int j : cur) {
                    used[j] = true;
                }
                res.push_back(cur);
            }
        }
        return res;
    }
    void unite(int u, int v) {
        swap(next[u], next[v]);
    }
} tcc;

const int N = 2e5 + 10;
vector<int> g[N];
int in[N], out[N], timer;
int low[N], deg[N], path[N];
bool used[N];

void absorb(int u, int v) {
    tcc.unite(u, v);
    deg[u] += deg[v];
};

void dfs(int v, int p) {
    used[v] = true;
    in[v] = timer++;
    for (int to : g[v]) {
        if (to == v) {
            continue;
        }
        if (to == p) {
            p = N;
            continue;
        }
        if (used[to]) {
            if (in[to] < in[v]) {
                deg[v]++;
                low[v] = min(low[v], in[to]);
            }
            else {
                deg[v]--;
                int u = path[v];
                while (u != N && in[u] <= in[to] && in[to] < out[u]) {
                    absorb(v, u);
                    u = path[u];
                }
                path[v] = u;
            }
            continue;
        }
        dfs(to, v);
        if (path[to] == N && deg[to] <= 1) {
            deg[v] += deg[to];
            low[v] = min(low[v], low[to]);
            continue;
        }
        else if (deg[to] == 0) {
            to = path[to];
        }
        if (low[to] < low[v]) {
            low[v] = low[to];
            swap(to, path[v]);
        }
        while (to != N) {
            absorb(v, to);
            to = path[to];
        }
    }
    out[v] = timer;
};

vector<vector<int>> three_edge_connectivity(int n) {
    for (int i = 1; i <= n; i++) {
        in[i] = 0;
        out[i] = 0;
        low[i] = N;
        deg[i] = 0;
        path[i] = N;
        used[i] = false;
    }
    tcc.init(n);
    timer = 0;
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs(i, N);
        }
    }
    return tcc.get_all(n);
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