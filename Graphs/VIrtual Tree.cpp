#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// ==================== WARNING ====================
// SPARSE TABLE N MUST BE 2X BIGGER THAN GRAPH N (because of euler tour)
// tested on: https://codeforces.com/contest/1320/submission/260980762 + stress test

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

int par_vir[N];
vector<int> g_vir[N];
bool flag_vir[N];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        depth[i] = 0;
        in[i] = 0;
        out[i] = 0;
        g[i].clear();
    }
    tour.clear();

    for (int i = 1; i <= n; i++) {
        par_vir[i] = 0;
        g_vir[i].clear();
        flag_vir[i] = false;
    }
}

void init_vir(const vector<int>& all) {
    for (int v : all) {
        par_vir[v] = 0;
        g_vir[v].clear();
        flag_vir[v] = false;
    }
}

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

pair<vector<int>, int> get_virtual_tree(const vector<int>& vers) {
    vector<pair<int, int>> ord;
    for (int v : vers) {
        ord.emplace_back(in[v], v);
    }
    sort(ord.begin(), ord.end());
    ord.erase(unique(ord.begin(), ord.end()), ord.end());
    vector<int> all = vers;
    for (int i = 0; i + 1 < ord.size(); i++) {
        int u = ord[i].second;
        int v = ord[i + 1].second;
        all.push_back(lca(u, v));
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());

    for (int v : all) {
        assert(g_vir[v].empty() && par_vir[v] == 0);
    }

    vector<pair<int, int>> scn;
    for (int v : all) {
        scn.emplace_back(in[v], v);
        scn.emplace_back(out[v], v);
    }
    sort(scn.begin(), scn.end());
    stack<int> st;
    for (auto [t, v] : scn) {
        if (!flag_vir[v]) {
            st.push(v);
        } else {
            st.pop();
            par_vir[v] = st.empty() ? 0 : st.top();
            if (par_vir[v]) {
                g_vir[par_vir[v]].push_back(v);
            }
        }
        flag_vir[v] ^= 1;
    }
    int root = 0;
    for (int v : all) {
        if (par_vir[v] == 0) {
            root = v;
        }
    }
    return {all, root};
}

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