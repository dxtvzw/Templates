#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

struct segment_tree {
    static const int N = 1e6 + 10;
    ll t[2 * N + 10];
    void build() {
        for (int i = N - 1; i > 0; i--) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }
    void update(int pos, ll val) {
        for (t[pos += N] = val; pos > 1; pos >>= 1) {
            t[pos >> 1] = t[pos] + t[pos ^ 1];
        }
    }
    ll get(int l, int r) {
        ll res = 0;
        for (l += N, r += N; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (!(r & 1)) res += t[r--];
        }
        return res;
    }
} tree;

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
