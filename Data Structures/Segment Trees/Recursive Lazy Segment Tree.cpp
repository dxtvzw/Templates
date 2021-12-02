#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct lazy_segment_tree {
    static const int N = 1e6 + 10;
    const T inf = numeric_limits<T>::max() / 2;
    const T good_value = 0; // 0 for sum, -inf for max, and inf for min
    T a[N], t[4 * N], ch[4 * N];
    T merge(T a, T b) {
        return a + b;
    }
    void build(int v = 1, int tl = 1, int tr = N - 1) {
        if (tl == tr) {
            t[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(v + v, tl, tm);
        build(v + v + 1, tm + 1, tr);
        t[v] = merge(t[v + v], t[v + v + 1]);
    }
    void push(int v, int tl, int tr) {
        if (!ch[v]) return;
        t[v] += ch[v] * (tr - tl + 1); // tr - tl + 1 for sum and 1 for min/max
        if (tl < tr) {
            ch[v + v] += ch[v];
            ch[v + v + 1] += ch[v];
        }
        ch[v] = 0;
    }
    void update(int l, int r, T x, int v = 1, int tl = 1, int tr = N - 1) {
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
    T get(int l, int r, int v = 1, int tl = 1, int tr = N - 1) {
        push(v, tl, tr);
        if (r < tl || tr < l) return good_value;
        if (l <= tl && tr <= r) return t[v];
        int tm = (tl + tr) / 2;
        T res = merge(get(l, r, v + v, tl, tm), get(l, r, v + v + 1, tm + 1, tr));
        t[v] = merge(t[v + v], t[v + v + 1]);
        return res;
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