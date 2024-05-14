#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct persistent_segment_tree {
    static const int N = 2e5 + 10;
    static const int L = 20;
    static const int S = N * L;
    const T inf = 1e9;
    const T good_value = 0;

    T t[S];
    int lef[S], rig[S];
    int roots[N], sz = 0, rt = 0;

    void init() {
        for (int i = 1; i <= sz; i++) {
            t[i] = lef[i] = rig[i] = 0;
        }
        for (int i = 1; i <= rt; i++) {
            roots[i] = 0;
        }
        sz = rt = 0;
    }
    T merge(T a, T b) {
        return a + b;
    }
    int copy(int v) {
        ++sz;
        lef[sz] = lef[v];
        rig[sz] = rig[v];
        t[sz] = t[v];
        return sz;
    }
    int make_root(int r) {
        roots[++rt] = copy(roots[r]);
        return rt;
    }
    void my_update(int pos, T val, int v, int tl = 0, int tr = N - 1) {
        if (tl == tr) {
            t[v] += val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            my_update(pos, val, lef[v] = copy(lef[v]), tl, tm);
        } else {
            my_update(pos, val, rig[v] = copy(rig[v]), tm + 1, tr);
        }
        t[v] = merge(t[lef[v]], t[rig[v]]);
    }
    T my_get(int l, int r, int v, int tl = 0, int tr = N - 1) {
        if (l > r || tl > r || l > tr) return good_value;
        if (l <= tl && tr <= r) return t[v];
        int tm = (tl + tr) / 2;
        return merge(my_get(l, r, lef[v], tl, tm), my_get(l, r, rig[v], tm + 1, tr));
    }
    int update(int pos, T val) {
        int vrs = make_root(rt);
        my_update(pos, val, roots[vrs]);
        return vrs;
    }
    T get(int l, int r, int version) {
        if (!version) return 0;
        return my_get(l, r, roots[version]);
    }
};

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