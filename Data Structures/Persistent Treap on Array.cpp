#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128_t LL;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define F first
#define S second
#define pb push_back
mt19937 rnd(time(0));

struct Node {
    int val, sz, uni, cnt, l, r;
};

typedef Node* pNode;
typedef pair<pNode, pNode> ppn;

const int N = 3e5 + 10;
const int L = 33;
const int M = 1e7 + 5e5 + 5e4;
int cnt_nodes;
Node nodes[M];
int roots[N];

int newNode(int _val) {
    assert(cnt_nodes + 1 < M);
    nodes[++cnt_nodes] = {_val, 1, 1, 1, 0, 0};
    return cnt_nodes;
}

int& l(int t) {
    return nodes[t].l;
}

int& r(int t) {
    return nodes[t].r;
}

int& sz(int t) {
    return nodes[t].sz;
}

int& val(int t) {
    return nodes[t].val;
}

int& uni(int t) {
    return nodes[t].uni;
}

int& cnt(int t) {
    return nodes[t].cnt;
}

void recalc(int t) {
    if (!t) return;
    nodes[t].sz = sz(l(t)) + sz(r(t)) + 1;
    nodes[t].uni = uni(l(t)) + uni(r(t)) + (cnt(t) == 1);
}

int Copy(int v) {
    if (!v) return v;
    int cur = newNode(0);
    nodes[cur] = nodes[v];
    return cur;
}

int Merge(int t1, int t2) {
    if (!t1) return t2;
    if (!t2) return t1;
    int res = 0;
    if (rnd() % (sz(t1) + sz(t2)) + 1 <= sz(t1)) {
        res = Copy(t1);
        r(res) = Merge(r(t1), t2);
    }
    else {
        res = Copy(t2);
        l(res) = Merge(t1, l(t2));
    }
    recalc(res);
    return res;
}

pii Split_pref(int t, int k) {
    if (sz(t) <= k) {
        return {t, 0};
    }
    else if (sz(l(t)) + 1 <= k) {
        pii nxt = Split_pref(r(t), k - sz(l(t)) - 1);
        int res = Copy(t);
        r(res) = nxt.F;
        recalc(res);
        return {res, nxt.S};
    }
    else {
        pii nxt = Split_pref(l(t), k);
        int res = Copy(t);
        l(res) = nxt.S;
        recalc(res);
        return {nxt.F, res};
    }
}

void dfs_print(int v) {
    if (!v) return;
    if (l(v)) dfs_print(l(v));
    cout << "(" << v << ", " << val(v) << ", " << cnt(v) << ") ";
    if (r(v)) dfs_print(r(v));
}

pii find(int v, int x) {
    if (!v) return {0, 0};
    if (val(v) < x) {
        pii res = find(r(v), x);
        res.S += sz(l(v)) + 1;
        return res;
    }
    else if (val(v) == x) {
        return {v, sz(l(v)) + 1};
    }
    else {
        return find(l(v), x);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif



#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}

