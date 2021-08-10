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

template <typename T>
struct segment_tree {
    static const int N = 1e6 + 10;
    const T inf = numeric_limits<T>::max() / 2;
    const T good_value = 0; // 0 for sum, -inf for max, and inf for min
    T a[N], t[4 * N];
    T merge(T x, T y) {
        return x + y;
    }
    void build(int v = 1, int tl = 1, int tr = N - 1) {
        if (tl > tr) return;
        if (tl == tr) {
            t[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(v + v, tl, tm);
        build(v + v + 1, tm + 1, tr);
        t[v] = merge(t[v + v], t[v + v + 1]);
    }
    void update(int pos, T val, int v = 1, int tl = 1, int tr = N - 1) {
        if (tl > tr || tl > pos || pos > tr) return;
        if (tl == tr) {
            t[v] = val;
            return;
        }
        int tm = (tl + tr) / 2;
        update(pos, val, v + v, tl, tm);
        update(pos, val, v + v + 1, tm + 1, tr);
        t[v] = merge(t[v + v], t[v + v + 1]);
    }
    T get(int l, int r, int v = 1, int tl = 1, int tr = N - 1) {
        if (tl > tr || l > r || tl > r || l > tr) return good_value;
        if (l <= tl && tr <= r) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return merge(get(l, r, v + v, tl, tm), get(l, r, v + v + 1, tm + 1, tr));
    }
};

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
