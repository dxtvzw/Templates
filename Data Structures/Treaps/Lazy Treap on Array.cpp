#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

std::mt19937 rnd;

/*
 * val -- value of node
 * sum -- sum of values in subtree
 * ch -- lazy propagation thing
 * idx -- abstract index of this node in array
 * in-order traversal gives left to right array
 * in-order traversal sorts nodes by idx
 */

typedef long long val_type;
typedef int idx_type;

struct Node {
    val_type val, sum, ch;
    idx_type idx;
    int prio, sz;
    int l, r;
    Node (int _val = 0, int _idx = 0) {
        val = _val;
        idx = _idx;
        sum = val;
        prio = rnd();
        sz = 1;
        l = 0;
        r = 0;
    }
};

const int MAX_NODES = 1e6 + 10;
int node_ptr = 0;
Node nodes[MAX_NODES];

int new_node(val_type val = 0, idx_type idx = 0) {
    nodes[++node_ptr] = Node(val, idx);
    return node_ptr;
}

int sz(int t) {
    return t == 0 ? 0 : nodes[t].sz;
}

val_type val(int t) {
    return t == 0 ? 0 : nodes[t].val;
}

val_type sum(int t) {
    return t == 0 ? 0 : nodes[t].sum;
}

val_type ch(int t) {
    return t == 0 ? 0 : nodes[t].ch;
}

idx_type idx(int t) {
    return t == 0 ? 0 : nodes[t].idx;
}

void push(int t) {
    if (!t || nodes[t].ch == 0) return;
    nodes[t].val += nodes[t].ch;
    nodes[t].sum += nodes[t].ch * nodes[t].sz;
    if (nodes[t].l) nodes[nodes[t].l].ch += nodes[t].ch;
    if (nodes[t].r) nodes[nodes[t].r].ch += nodes[t].ch;
    nodes[t].ch = 0;
}

void recalc(int t) {
    if (!t) return;
    push(nodes[t].l);
    push(nodes[t].r);
    nodes[t].sum = sum(nodes[t].l) + sum(nodes[t].r) + val(t);
    nodes[t].sz = sz(nodes[t].l) + sz(nodes[t].r) + 1;
}

void update(int t, val_type val) {
    if (!t) return;
    nodes[t].ch += val;
    push(t);
}

int merge(int t1, int t2) {
    push(t1);
    push(t2);
    if (t1 == 0) return t2;
    if (t2 == 0) return t1;
    int res = 0;
    if (nodes[t1].prio < nodes[t2].prio) {
        res = t1;
        nodes[res].r = merge(nodes[t1].r, t2);
    } else {
        res = t2;
        nodes[res].l = merge(t1, nodes[t2].l);
    }
    recalc(res);
    return res;
}

template <typename... Args>
int merge(int first, Args... args) {
    return merge(first, merge(args...));
}

// split first k elements
pair<int, int> split(int t, int k) {
    push(t);
    if (sz(t) <= k) {
        return {t, 0};
    } else if (sz(nodes[t].l) + 1 <= k) {
        auto [lef, rig] = split(nodes[t].r, k - sz(nodes[t].l) - 1);
        nodes[t].r = lef;
        recalc(t);
        return {t, rig};
    } else {
        auto [lef, rig] = split(nodes[t].l, k);
        nodes[t].l = rig;
        recalc(t);
        return {lef, t};
    }
}

// split [1, lef - 1], [lef, rig], [rig + 1, size(tree)]
tuple<int, int, int> split_subseg(int t, int lef, int rig) {
    push(t);
    pair<int, int> a = split(t, lef - 1);
    pair<int, int> b = split(a.second, rig - lef + 1);
    return {a.first, b.first, b.second};
}

// splits to (-inf, idx) and [idx, +inf) by index
pair<int, int> split_less(int t, idx_type idx) {
    push(t);
    if (t == 0) {
        return {0, 0};
    } else if (nodes[t].idx < idx) {
        auto [lef, rig] = split_less(nodes[t].r, idx);
        nodes[t].r = lef;
        recalc(t);
        return {t, rig};
    } else {
        auto [lef, rig] = split_less(nodes[t].l, idx);
        nodes[t].l = rig;
        recalc(t);
        return {lef, t};
    }
}

// split into (-inf, idx) [idx, idx] (idx, +inf) by index
tuple<int, int, int> split_idx(int t, idx_type idx) {
    push(t);
    if (t == 0) {
        return {0, 0, 0};
    } else if (nodes[t].idx == idx) {
        int lef = nodes[t].l;
        int rig = nodes[t].r;
        nodes[t].l = nodes[t].r = 0;
        recalc(t);
        return {lef, t, rig};
    } else if (nodes[t].idx < idx) {
        auto [lef, mid, rig] = split_idx(nodes[t].r, idx);
        nodes[t].r = lef;
        recalc(t);
        return {t, mid, rig};
    } else {
        auto [lef, mid, rig] = split_idx(nodes[t].l, idx);
        nodes[t].l = rig;
        recalc(t);
        return {lef, mid, t};
    }
}

// split into (-inf, l), [l, r], (r, +inf) by index
tuple<int, int, int> split_subseg_idx(int t, idx_type l, idx_type r) {
    auto [lef, mid_rig] = split_less(t, l);
    auto [mid, rig] = split_less(mid_rig, r + 1);
    return {lef, mid, rig};
}

// print as real array
void dfs_print_val(int v) {
    push(v);
    if (v == 0) return;
    if (nodes[v].l) dfs_print_val(nodes[v].l);
    cout << nodes[v].val << " ";
    if (nodes[v].r) dfs_print_val(nodes[v].r);
}

// collect nodes into real array
void dfs_get(int v, vector<Node>& vec) {
    push(v);
    if (v == 0) return;
    if (nodes[v].l) dfs_get(nodes[v].l, vec);
    vec.push_back(nodes[v]);
    if (nodes[v].r) dfs_get(nodes[v].r, vec);
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