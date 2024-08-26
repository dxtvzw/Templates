#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// tested on https://acm.timus.ru/problem.aspx?space=1&num=1553 for vertices
// tested on https://codeforces.com/contest/1555/problem/F for edges
// stress tested (see below)

constexpr bool weighted_edges = true; // true if weights are on edges || false if weights are on vertices
constexpr bool double_vertices = false; // double vertices for distinct tin[v], tout[v]

// update all below and push in segment tree
using weight_type = ll;
const weight_type inf = numeric_limits<weight_type>::max() / 2 - 100;
const weight_type good_value = 0;

weight_type merge(weight_type a, weight_type b) {
    return a + b;
}

const int N = 3e5 + 10;
const int N2 = double_vertices ? N + N : N;
const int L = 20;

struct lazy_segment_tree {
    weight_type a[N2], t[4 * N2], ch[4 * N2];
    void build(int v = 1, int tl = 0, int tr = N2 - 1) {
        ch[v] = 0;
        if (tl == tr) {
            t[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(v + v, tl, tm);
        build(v + v + 1, tm + 1, tr);
        t[v] = merge(t[v + v], t[v + v + 1]);
    }
    void init(int l, int r, weight_type val = good_value, int v = 1, int tl = 0, int tr = N2 - 1) {
        ch[v] = 0;
        if (r < tl || tr < l) {
            return;
        } else if (tl == tr) {
            t[v] = val;
        } else {
            int tm = (tl + tr) / 2;
            init(l, r, val, v + v, tl, tm);
            init(l, r, val, v + v + 1, tm + 1, tr);
            t[v] = merge(t[v + v], t[v + v + 1]);
        }
    }
    void push(int v, int tl, int tr) {
        if (!ch[v]) return;
        t[v] += ch[v] * (tr - tl + 1); // =============================== CHANGE ===============================
        if (tl < tr) {
            ch[v + v] += ch[v];
            ch[v + v + 1] += ch[v];
        }
        ch[v] = 0;
    }
    void update(int l, int r, weight_type x, int v = 1, int tl = 0, int tr = N2 - 1) {
        push(v, tl, tr);
        if (r < tl || tr < l) return;
        if (l <= tl && tr <= r) {
            ch[v] += x;
            push(v, tl, tr);
            return;
        }
        int tm = (tl + tr) / 2;
        update(l, r, x, v + v, tl, tm);
        update(l, r, x, v + v + 1, tm + 1, tr);
        t[v] = merge(t[v + v], t[v + v + 1]);
    }
    weight_type get(int l, int r, int v = 1, int tl = 0, int tr = N2 - 1) {
        push(v, tl, tr);
        if (r < tl || tr < l) return good_value;
        if (l <= tl && tr <= r) return t[v];
        int tm = (tl + tr) / 2;
        weight_type res = merge(get(l, r, v + v, tl, tm), get(l, r, v + v + 1, tm + 1, tr));
        t[v] = merge(t[v + v], t[v + v + 1]);
        return res;
    }
};

lazy_segment_tree tree;

vector<int> g[N];
int up[N][L];
int depth[N];
int sz[N];

int tin[N], tout[N], timer;
int ord[N2];
int heavy_child[N];
int head[N];

void init(int n) {
    tree.init(1, double_vertices ? 2 * n : n, 0);
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        for (int j = 0; j < L; j++) {
            up[i][j] = 0;
        }
        depth[i] = 0;
        sz[i] = 0;
        tin[i] = 0;
        tout[i] = 0;
        heavy_child[i] = 0;
        head[i] = 0;
    }
    for (int i = 1; i <= (double_vertices ? 2 * n : n); i++) {
        ord[i] = 0;
    }
    timer = 0;
}

void dfs_hld1(int v, int p) {
    up[v][0] = p;
    for (int i = 1; i < L; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    sz[v] = 1;
    for (int to : g[v]) {
        if (to != p) {
            depth[to] = depth[v] + 1;
            dfs_hld1(to, v);
            sz[v] += sz[to];
        }
    }
}

void dfs_hld2(int v, int p) {
    tin[v] = ++timer;
    ord[tin[v]] = v;
    heavy_child[v] = 0;
    for (int to : g[v]) {
        if (to != p) {
            if (heavy_child[v] == 0 || sz[to] > sz[heavy_child[v]]) {
                heavy_child[v] = to;
            }
        }
    }
    if (heavy_child[v]) {
        head[heavy_child[v]] = head[v];
        dfs_hld2(heavy_child[v], v);
    }
    for (int to : g[v]) {
        if (to != p && to != heavy_child[v]) {
            head[to] = to;
            dfs_hld2(to, v);
        }
    }
    tout[v] = timer;
}

void decomposition(int v) {
    dfs_hld1(v, v);
    dfs_hld2(v, v);
}

bool is_anc(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v) {
    if (is_anc(u, v)) {
        return u;
    } else if (is_anc(v, u)) {
        return v;
    } else {
        for (int i = L - 1; i >= 0; i--) {
            if (!is_anc(up[u][i], v)) {
                u = up[u][i];
            }
        }
        return up[u][0];
    }
}

void update_path(int u, int v, ll val, bool handled = false) {
    if (is_anc(u, v)) {
        while (u != v) {
            if (head[v] == v) { // up[v][0] -> v -- light edge
                tree.update(tin[v], tin[v], val);
                v = up[v][0];
            } else {
                int z = heavy_child[head[u] == head[v] ? u : head[v]];
                tree.update(tin[z], tin[v], val);
                v = head[u] == head[v] ? u : head[v];
            }
        }
        if (!weighted_edges && !handled) {
            tree.update(tin[u], tin[u], val);
        }
    } else if (is_anc(v, u)) {
        update_path(v, u, val);
    } else {
        int l = lca(u, v);
        update_path(l, u, val, weighted_edges);
        update_path(l, v, val, true);
    }
}

void update_subtree(int v, ll val) {
    tree.update(tin[v] + weighted_edges, tout[v], val);
}

weight_type get_path(int u, int v, bool handled = false) {
    if (is_anc(u, v)) {
        weight_type res = good_value;
        while (u != v) {
            if (head[v] == v) { // up[v][0] -> v -- light edge
                res = merge(res, tree.get(tin[v], tin[v]));
                v = up[v][0];
            } else {
                int z = heavy_child[head[u] == head[v] ? u : head[v]];
                res = merge(res, tree.get(tin[z], tin[v]));
                v = head[u] == head[v] ? u : head[v];
            }
        }
        if (!weighted_edges && !handled) {
            res = merge(res, tree.get(tin[u], tin[u]));
        }
        return res;
    } else if (is_anc(v, u)) {
        return get_path(v, u);
    } else {
        int l = lca(u, v);
        weight_type res = good_value;
        res = merge(res, get_path(l, u, weighted_edges));
        res = merge(res, get_path(l, v, true));
        return res;
    }
}

weight_type get_subtree(int v) {
    return tree.get(tin[v] + weighted_edges, tout[v]);
}

// =====================================================================================================================

namespace slow {
    int depth[N];
    int par[N];
    ll a[N];
    void init(int n) {
        for (int i = 1; i <= n; i++) {
            a[i] = 0;
            depth[i] = 0;
            par[i] = 0;
        }
    }
    void dfs(int v) {
        for (int to : g[v]) {
            if (to != par[v]) {
                par[to] = v;
                depth[to] = depth[v] + 1;
                dfs(to);
            }
        }
    }
    void update_path(int u, int v, ll val) {
        while (depth[u] > depth[v]) {
            a[u] += val;
            u = par[u];
        }
        while (depth[v] > depth[u]) {
            a[v] += val;
            v = par[v];
        }
        while (u != v) {
            a[u] += val;
            u = par[u];
            a[v] += val;
            v = par[v];
        }
        if (!weighted_edges) {
            a[v] += val;
        }
    }
    void update_subtree_impl(int v, ll val) {
        for (int to : g[v]) {
            if (to != par[v]) {
                a[to] += val;
                update_subtree_impl(to, val);
            }
        }
    }
    void update_subtree(int v, ll val) {
        if (!weighted_edges) {
            a[v] += val;
        }
        update_subtree_impl(v, val);
    }
    ll get_path(int u, int v) {
        ll res = good_value;
        while (depth[u] > depth[v]) {
            res = merge(res, a[u]);
            u = par[u];
        }
        while (depth[v] > depth[u]) {
            res = merge(res, a[v]);
            v = par[v];
        }
        while (u != v) {
            res = merge(res, a[u]);
            u = par[u];
            res = merge(res, a[v]);
            v = par[v];
        }
        if (!weighted_edges) {
            res = merge(res, a[v]);
        }
        return res;
    }
    ll get_subtree_impl(int v) {
        ll res = good_value;
        for (int to : g[v]) {
            if (to != par[v]) {
                res = merge(res, a[to]);
                res = merge(res, get_subtree_impl(to));
            }
        }
        return res;
    }
    ll get_subtree(int v) {
        ll res = good_value;
        if (!weighted_edges) {
            res = merge(res, a[v]);
        }
        res = merge(res, get_subtree_impl(v));
        return res;
    }
}

struct Query {
    int type;
    int u, v;
    ll val;
};

void stress() {
    const int max_n = 1 << 15;
    const int max_q = 1 << 15;
    const ll max_val = 1ll << 30;
    const bool can_neg = true;
    mt19937 rnd;
    auto gen = [&]() {
        ll val = (ll(rnd()) << 30) + ll(rnd());
        if (can_neg) {
            return val % (2 * max_val + 1) - max_val;
        } else {
            return val % max_val + 1;
        }
    };
    while (true) {
        int n = rnd() % max_n + 1;

        init(n);
        slow::init(n);

        for (int i = 2; i <= n; i++) {
            int j = rnd() % (i - 1) + 1;
            g[i].push_back(j);
            g[j].push_back(i);
        }

        decomposition(1);
        slow::dfs(1);

        int q = rnd() % max_q + 1;
        vector<Query> ques;
        for (int i = 0; i < q; i++) {
            int type = rnd() % 4 + 1;
            if (type == 1) {
                int u = rnd() % n + 1;
                int v = rnd() % n + 1;
                ll val = gen();
                ques.emplace_back(type, u, v, val);
            } else if (type == 2) {
                int v = rnd() % n + 1;
                ll val = gen();
                ques.emplace_back(type, 0, v, val);
            } else if (type == 3) {
                int u = rnd() % n + 1;
                int v = rnd() % n + 1;
                ques.emplace_back(type, u, v, 0);
            } else {
                int v = rnd() % n + 1;
                ques.emplace_back(type, 0, v, 0);
            }
        }

        vector<ll> ans;
        vector<ll> res;
        for (const auto& que : ques) {
            auto [type, u, v, val] = que;
            if (type == 1) {
                update_path(u, v, val);
                slow::update_path(u, v, val);
            } else if (type == 2) {
                update_subtree(v, val);
                slow::update_subtree(v, val);
            } else if (type == 3) {
                ans.push_back(get_path(u, v));
                res.push_back(slow::get_path(u, v));
            } else {
                ans.push_back(get_subtree(v));
                res.push_back(slow::get_subtree(v));
            }
        }

        if (ans == res) {
            cout << "OK" << endl;
        } else {
            cout << "WA\n";
            cout << n << "\n";
            for (int i = 1; i <= n; i++) {
                for (int j : g[i]) {
                    if (i < j) {
                        cout << i << " " << j << "\n";
                    }
                }
            }
            cout << q << "\n";
            for (const auto& que : ques) {
                auto [type, u, v, val] = que;
                if (type == 1) {
                    cout << type << " " << u << " " << v << " " << val << "\n";
                } else if (type == 2) {
                    cout << type << " " << v << " " << val << "\n";
                } else if (type == 3) {
                    cout << type << " " << u << " " << v << "\n";
                } else {
                    cout << type << " " << v << "\n";
                }
            }
            cout << "\n";
            for (ll x : ans) {
                cout << x << "\n";
            }
            cout << "\n";
            for (ll x : res) {
                cout << x << "\n";
            }
            break;
        }
    }
    exit(0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    stress();

    int n;
    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    decomposition(1);
    slow::dfs(1);
    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, v;
            ll val;
            cin >> u >> v >> val;
            update_path(u, v, val);
            slow::update_path(u, v, val);
        } else if (type == 2) {
            int v;
            ll val;
            cin >> v >> val;
            update_subtree(v, val);
            slow::update_subtree(v, val);
        } else if (type == 3) {
            int u, v;
            cin >> u >> v;
            cout << get_path(u, v) << "\t" << slow::get_path(u, v) << "\n";
        } else {
            int v;
            cin >> v;
            cout << get_subtree(v) << "\t" << slow::get_subtree(v) << "\n";
        }
    }

#ifdef LOCAL
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
}
