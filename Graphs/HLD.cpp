#include <bits/stdc++.h>

using namespace std;

// tested on https://acm.timus.ru/problem.aspx?space=1&num=1553 for vertices
// tested on https://codeforces.com/contest/1555/problem/F for edges

// CHECK UPDATE OF THE SEGMENT TREE

const bool hld_type = true; // false is for weighted vertices, true is for weighted edges
const int N = 3e5 + 10;
const int L = 20;
const int inf = 1e9 + 10;
const int good_value = 0; // change this according to the merge operation

int merge(int a, int b) {
    return a + b;
}

struct segment_tree {
    int t[2 * N + 5];
    void build() {
        for (int i = N - 1; i > 0; i--) {
            t[i] = merge(t[i << 1], t[i << 1 | 1]);
        }
    }
    void update(int pos, int val) {
        for (t[pos += N] += val; pos > 1; pos >>= 1) {
            t[pos >> 1] = merge(t[pos], t[pos ^ 1]);
        }
    }
    int get(int l, int r) {
        int res = good_value;
        for (l += N, r += N; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res = merge(res, t[l++]);
            if (!(r & 1)) res = merge(res, t[r--]);
        }
        return res;
    }
} tree;

/*
    tree_ptr - first unused position in the segment tree
    down[v] - child of v in its heavy path
    start[i] - array of starting positions of each heavy path
    st_prt - pointer to the first available cell in start[i]
    path_st[v] - highest vertex on v's heavy path
    pos[v] - position of v in the segment tree
*/

int timer, tree_ptr;
vector<int> g[N];
int in[N], out[N];
int up[N][L], down[N];
int sz[N], depth[N];
int start[N], st_ptr;
int path_st[N], pos[N];

bool is_heavy(int v, int to) {
    return sz[to] >= (sz[v] + 1) / 2;
}

void dfs_hld(int v = 1, int p = 1) {
    in[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i < L; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    sz[v] = 1;
    for (int to : g[v]) {
        if (to != p) {
            depth[to] = depth[v] + 1;
            dfs_hld(to, v);
            sz[v] += sz[to];
        }
    }
    bool light = 1;
    for (int to : g[v]) {
        if (to != p && is_heavy(v, to)) {
            light = 0;
            break;
        }
    }
    if (light) {
        start[st_ptr++] = v;
    }
    out[v] = ++timer;
}

bool is_anc(int u, int v) {
    return in[u] <= in[v] && in[v] <= out[u];
}

int lca(int u, int v) {
    if (is_anc(u, v)) return u;
    else if (is_anc(v, u)) return v;
    for (int i = L - 1; i >= 0; i--) {
        if (!is_anc(up[u][i], v)) u = up[u][i];
    }
    return up[u][0];
}

int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

void heavy_light_decomposition(int root = 1) {
    int mem = st_ptr;
    dfs_hld(root, root);
    for (int i = mem; i < st_ptr; i++) {
        int v = start[i];
        while (v != root && is_heavy(up[v][0], v)) {
            down[up[v][0]] = v;
            v = up[v][0];
        }
        int cur_st = v;
        while (v) {
            path_st[v] = cur_st;
            pos[v] = tree_ptr++;
            v = down[v];
        }
    }
}

void update(int v, int val) {
    tree.update(pos[v], val);
}

int get(int u, int v, bool flag = false) {
    if (is_anc(u, v)) {
        int res = good_value;
        while (path_st[v] != path_st[u]) {
            res = merge(res, tree.get(pos[path_st[v]], pos[v]));
            v = up[path_st[v]][0];
        }
        res = merge(res, tree.get(pos[u] + (hld_type || flag), pos[v]));
        return res;
    }
    else if (is_anc(v, u)) {
        return get(v, u);
    }
    else {
        int l = lca(u, v);
        return merge(get(l, u), get(l, v, true));
    }
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