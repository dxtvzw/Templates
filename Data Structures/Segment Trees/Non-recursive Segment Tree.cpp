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
    T t[2 * N + 10];
    void build() {
        for (int i = N - 1; i > 0; i--) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }
    void update(int pos, T val) {
        for (t[pos += N] = val; pos > 1; pos >>= 1) {
            t[pos >> 1] = t[pos] + t[pos ^ 1];
        }
    }
    T get(int l, int r) {
        T res = 0;
        for (l += N, r += N; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (!(r & 1)) res += t[r--];
        }
        return res;
    }
};

template <typename T>
struct segment_tree_min {
    static const int N = 1e6 + 10;
    const T inf = numeric_limits<T>::max() / 2;
    T t[2 * N + 10];
    void build() {
        for (int i = N - 1; i > 0; i--) {
            t[i] = min(t[i << 1], t[i << 1 | 1]);
        }
    }
    void update(int pos, T val) {
        for (t[pos += N] = val; pos > 1; pos >>= 1) {
            t[pos >> 1] = min(t[pos], t[pos ^ 1]);
        }
    }
    T get(int l, int r) {
        T res = inf;
        for (l += N, r += N; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res = min(res, t[l++]);
            if (!(r & 1)) res = min(res, t[r--]);
        }
        return res;
    }
};

template <typename T>
struct segment_tree_max {
    static const int N = 1e6 + 10;
    const T inf = numeric_limits<T>::max() / 2;
    T t[2 * N + 10];
    void build() {
        for (int i = N - 1; i > 0; i--) {
            t[i] = max(t[i << 1], t[i << 1 | 1]);
        }
    }
    void update(int pos, T val) {
        for (t[pos += N] = val; pos > 1; pos >>= 1) {
            t[pos >> 1] = max(t[pos], t[pos ^ 1]);
        }
    }
    T get(int l, int r) {
        T res = -inf;
        for (l += N, r += N; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, t[l++]);
            if (!(r & 1)) res = max(res, t[r--]);
        }
        return res;
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
