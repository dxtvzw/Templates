#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
 * TOUR SIZE IS TWO TIMES MORE THAN N, SO UPDATE SPARSE_TABLE::N CORRESPONDINGLY
 *
 * checked on this problem: https://codeforces.com/problemset/problem/342/E
 */

enum TableType { VAL, ARG };

template <typename T, TableType S = TableType::VAL, typename Cmp = less<T>>
struct sparse_table{
    // VAL returns value, ARG returns position of value
    // less<> for minimum, greater<> for maximum
    // d[i][j] = min(a[i], a[i + 1], ... , a[i + (1 << j) - 1])
    // get(l, r) = min(a[l], a[l + 1], ... , a[r])
    static const int N = 2e5 + 10;
    static const int L = 19;
    T a[N];
    int d[N][L], rem[N];
    void build(int n, Cmp cmp = {}) {
        for (int i = 1; i <= n; i++) { d[i][0] = i; }
        for (int j = 1; j <= L - 1; j++) {
            for (int i = 1; i <= n; i++) {
                if (i + (1 << j) - 1 > n) { continue; }
                d[i][j] = cmp(a[d[i][j - 1]], a[d[i + (1 << (j - 1))][j - 1]]) ? d[i][j - 1] : d[i + (1 << (j - 1))][j - 1];
            }
        }
        for (int i = 1; i <= n; i++) { rem[i] = log2(i); }
    }
    T get(int l, int r, Cmp cmp = {}) {
        int lg = rem[r - l + 1];
        int pos = cmp(a[d[l][lg]], a[d[r - (1 << lg) + 1][lg]]) ? d[l][lg] : d[r - (1 << lg) + 1][lg];
        if constexpr (S == TableType::VAL) { return a[pos]; } else { return pos; }
    }
};

sparse_table<int, TableType::ARG> table;

const int N = 1e5 + 10;
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

void precalc_lca() {
    dfs_lca();
    for (int i = 1; i <= tour.size(); i++) {
        table.a[i] = depth[tour[i - 1]];
    }
    table.build(tour.size());
}

int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

bool used_centr[N];
int sz[N];
int par_centr[N];
int dp[N];

void dfs_sizes(int v, int p) {
    sz[v] = 1;
    for (int to : g[v]) {
        if (!used_centr[to] && to != p) {
            dfs_sizes(to, v);
            sz[v] += sz[to];
        }
    }
}

int centr_decomp(int root) {
    dfs_sizes(root, root);
    int tot = sz[root];
    for (int prev = -1;;) {
        int cur = -1;
        for (int to : g[root]) {
            if (!used_centr[to] && to != prev && sz[to] > tot / 2) {
                cur = to;
                break;
            }
        }
        if (cur == -1) {
            break;
        }
        prev = root;
        root = cur;
    }
    used_centr[root] = true;
    for (int to : g[root]) {
        if (!used_centr[to]) {
            int nxt = centr_decomp(to);
            par_centr[nxt] = root;
        }
    }
    return root;
}

void dfs_init(int v, int p) {
    for (int to : g[v]) {
        if (to != p) {
            dp[to] = dp[v] + 1;
            dfs_init(to, v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    centr_decomp(1);
    dfs_init(1, 1);
    precalc_lca();

    while (q--) {
        int type, v;
        cin >> type >> v;
        if (type == 1) {
            for (int u = v; u; u = par_centr[u]) {
                dp[u] = min(dp[u], dist(u, v));
            }
        } else {
            int ans = dp[v];
            for (int u = v; u; u = par_centr[u]) {
                ans = min(ans, dist(u, v) + dp[u]);
            }
            cout << ans << "\n";
        }
    }

#ifdef LOCAL
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
}