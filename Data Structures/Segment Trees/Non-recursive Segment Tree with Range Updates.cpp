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
struct lazy_segment_tree {
    static const int N = 1e6 + 10;
    T t[2 * N + 10];
    void update(int l, int r, T val) {
        for (l += N, r += N; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) t[l++] += val;
            if (!(r & 1)) t[r--] += val;
        }
    }
    T get(int pos) {
        T res = 0;
        for (pos += N; pos > 0; pos >>= 1) {
            res += t[pos];
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
