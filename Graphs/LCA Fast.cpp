#include <bits/stdc++.h>

using namespace std;

// ==================== WARNING ====================
// SPARSE TABLE N MUST BE 2X BIGGER THAN GRAPH N (because of euler tour)
// tested on: https://codeforces.com/contest/1320/submission/260980762

enum TableType { VAL, ARG };

template <typename T, TableType S = TableType::VAL, typename Cmp = less<T>>
struct sparse_table {
    static const int N = 4e5 + 10, L = 19;
    T a[N];
    int d[L][N];
    void build(int n, Cmp cmp = {}) {
        for (int i = 1; i <= n; i++) { d[0][i] = i; }
        for (int j = 1; j <= L - 1; j++) {
            for (int i = 1; i <= n; i++) {
                if (i + (1 << j) - 1 > n) { continue; }
                d[j][i] = cmp(a[d[j - 1][i]], a[d[j - 1][i + (1 << (j - 1))]]) ? d[j - 1][i] : d[j - 1][i + (1 << (j - 1))];
            }
        }
    }
    T get(int l, int r, Cmp cmp = {}) {
        int lg = __lg(r - l + 1);
        int pos = cmp(a[d[lg][l]], a[d[lg][r - (1 << lg) + 1]]) ? d[lg][l] : d[lg][r - (1 << lg) + 1];
        if constexpr (S == TableType::VAL) { return a[pos]; } else { return pos; }
    }
};

sparse_table<int, TableType::ARG> table;

const int N = 2e5 + 10;
int depth[N], in[N], out[N];
vector<int> g[N];
vector<int> tour;

void dfs_lca(int v = 1, int p = 1) {
    in[v] = tour.size();
    tour.push_back(v);
    for (int to : g[v]) {
        if (to != p) {
            depth[to] = depth[v] + 1;
            dfs_lca(to, v);
            tour.push_back(v);
        }
    }
    out[v] = tour.size() - 1;
}

int lca(int u, int v) {
    if (out[u] > out[v]) {
        swap(u, v);
    }
    return tour[table.get(in[u] + 1, out[v] + 1) - 1];
}

int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

void precalc_lca(int root = 1) {
    dfs_lca(root, root);
    for (int i = 1; i <= tour.size(); i++) {
        table.a[i] = depth[tour[i - 1]];
    }
    table.build(tour.size());
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