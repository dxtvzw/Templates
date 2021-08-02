#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

struct lazy_segment_tree {
    static const int N = 1e6 + 10;
    const ll inf = 1e18;
    const ll good_value = 0; // 0 for sum, -inf for max, and inf for min
    ll a[N], t[4 * N], ch[4 * N];
    ll merge(ll a, ll b) {
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
        t[v] += 1ll * ch[v] * (tr - tl + 1); // tr - tl + 1 for sum and 1 for min/max
        if (tl < tr) {
            ch[v + v] += ch[v];
            ch[v + v + 1] += ch[v];
        }
        ch[v] = 0;
    }
    void update(int l, int r, ll x, int v = 1, int tl = 1, int tr = N - 1) {
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
    ll get(int l, int r, int v = 1, int tl = 1, int tr = N - 1) {
        push(v, tl, tr);
        if (r < tl || tr < l) return good_value;
        if (l <= tl && tr <= r) return t[v];
        int tm = (tl + tr) / 2;
        ll res = merge(get(l, r, v + v, tl, tm), get(l, r, v + v + 1, tm + 1, tr));
        t[v] = merge(t[v + v], t[v + v + 1]);
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
