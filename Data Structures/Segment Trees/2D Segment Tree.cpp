#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
 * Two-dimensional segment tree (segment tree in each node of segment tree)
 * Point update (a[x] := val)
 * Range query (max on [lx, rx] x [ly, ry])
 * See: https://contest.ucup.ac/submission/204187
 *
 * Notes: ALWAYS CALL BUILD TO INITIALIZE ALL TREES
 */

template <typename T>
struct small_tree {
    int n;
    vector<T> t;
    void init(int _n) {
        n = _n + 5;
        t.assign(2 * n + 10, 0);
    }
    void update(int pos, T val) {
        for (t[pos += n] = val; pos > 1; pos >>= 1) {
            t[pos >> 1] = max(t[pos], t[pos ^ 1]);
        }
    }
    T get(int l, int r) {
        T res = 0;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, t[l++]);
            if (!(r & 1)) res = max(res, t[r--]);
        }
        return res;
    }
};

vector<pair<int, int>> merge(const vector<pair<int, int>>& a, const vector<pair<int, int>>& b) {
    int n = a.size(), m = b.size();
    int i = 0, j = 0;
    vector<pair<int, int>> res;
    while (i < n && j < m) {
        if (a[i].first < b[j].first) {
            res.push_back(a[i++]);
        } else {
            res.push_back(b[j++]);
        }
    }
    while (i < n) {
        res.push_back(a[i++]);
    }
    while (j < m) {
        res.push_back(b[j++]);
    }
    return res;
}

template <typename T>
struct Node {
    small_tree<T> tree;
    int tl, tr;
    vector<pair<int, int>> all;
    vector<int> pos;
    Node(int x = 0, int y = 0) {
        tl = x;
        tr = x;
        all = {{y, x}};
        pos = {0};
        tree.init(1);
    }
    friend Node operator+(const Node& a, const Node& b) {
        Node res;
        res.tl = a.tl;
        res.tr = b.tr;
        res.all = merge(a.all, b.all);
        res.pos.resize(res.all.size());
        for (int i = 0; i < res.all.size(); i++) {
            res.pos[res.all[i].second - res.tl] = i;
        }
        res.tree.init(res.tr - res.tl + 1);
        return res;
    }
    void update(int x, T val) {
        assert(tl <= x && x <= tr);
        tree.update(pos[x - tl], val);
    }
    T get(int l, int r) {
        int L = lower_bound(all.begin(), all.end(), make_pair(l, 0)) - all.begin();
        int R = lower_bound(all.begin(), all.end(), make_pair(r + 1, 0)) - all.begin() - 1;
        L = max(0, L);
        R = min(R, tr - tl);
        if (L <= R) {
            return tree.get(L, R);
        } else {
            return 0;
        }
    }
};

template <typename T>
struct big_tree {
    static const int N = 2e5 + 10;
    int y_init[N];
    Node<T> t[4 * N];
    void build(int v = 1, int tl = 1, int tr = N - 1) {
        if (tl == tr) {
            t[v] = Node<T>(tl, y_init[tl]);
            return;
        }
        int tm = (tl + tr) / 2;
        build(v + v, tl, tm);
        build(v + v + 1, tm + 1, tr);
        t[v] = t[v + v] + t[v + v + 1];
    }
    void update(int x, int val, int v = 1, int tl = 1, int tr = N - 1) {
        if (x < tl || tr < x) return;
        t[v].update(x, val);
        if (tl == tr) {
            return;
        }
        int tm = (tl + tr) / 2;
        update(x, val, v + v, tl, tm);
        update(x, val, v + v + 1, tm + 1, tr);
    }
    T get(int lx, int rx, int ly, int ry, int v = 1, int tl = 1, int tr = N - 1) {
        if (tr < lx || rx < tl) return 0;
        if (lx <= tl && tr <= rx) {
            return t[v].get(ly, ry);
        }
        int tm = (tl + tr) / 2;
        return max(get(lx, rx, ly, ry, v + v, tl, tm), get(lx, rx, ly, ry, v + v + 1, tm + 1, tr));
    }
};

big_tree<int> tree;

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
