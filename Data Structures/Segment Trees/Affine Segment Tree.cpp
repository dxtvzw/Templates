#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

template <typename T>
struct Affine {
    T k = 1, b = 0;
    Affine(T k, T b) : k(k), b(b) {}
    Affine(T b) : k(1), b(b) {}
    Affine(int b) : k(1), b(b) {}
    Affine() {}
    bool operator==(const Affine& ot) const {
        return k == ot.k && b == ot.b;
    }
    Affine operator()(const Affine& ot) const {
        return {k * ot.k, k * ot.b + b};
    }
};

template <typename T>
struct affine_segment_tree {
    static const int N = 1e5 + 10;
    const T good_value = 0; // 0 for sum, -inf for max, and inf for min
    const Affine<T> good_affine = {};
    T a[N], t[4 * N];
    Affine<T> ch[4 * N];
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
        if (ch[v] == good_affine) return;
        t[v] = ch[v].k * t[v] + ch[v].b * (tr - tl + 1);
        if (tl < tr) {
            ch[v + v] = ch[v](ch[v + v]);
            ch[v + v + 1] = ch[v](ch[v + v + 1]);
        }
        ch[v] = good_affine;
    }
    void update(int l, int r, Affine<T> val, int v = 1, int tl = 1, int tr = N - 1) {
        push(v, tl, tr);
        if (r < tl || tr < l || l > r) return;
        if (l <= tl && tr <= r) {
            ch[v] = val(ch[v]);
            push(v, tl, tr);
            return;
        }
        int tm = (tl + tr) / 2;
        update(l, r, val, v + v, tl, tm);
        update(l, r, val, v + v + 1, tm + 1, tr);
        t[v] = merge(t[v + v], t[v + v + 1]);
    }
    T get(int l, int r, int v = 1, int tl = 1, int tr = N - 1) {
        push(v, tl, tr);
        if (r < tl || tr < l || l > r) return good_value;
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
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif



#ifdef LOCAL
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
}