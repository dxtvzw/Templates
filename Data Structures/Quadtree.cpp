#include <bits/stdc++.h>

using namespace std;

struct quadtree {
    static const int N = 2e3 + 10;
    int a[N][N];
    int t[2 * N * N + 10];
    inline int ld(int v) {
        return v * 4 + 1;
    }
    inline int lu(int v) {
        return v * 4 + 2;
    }
    inline int rd(int v) {
        return v * 4 + 3;
    }
    inline int ru(int v) {
        return v * 4 + 4;
    }
    void build(int v = 0, int tl = 1, int tr = N - 1, int td = 1, int tu = N - 1) {
        if (tl > tr || td > tu) return;
        if (tl == tr && td == tu) {
            t[v] = a[tl][td];
            return;
        }
        int x = (tl + tr) / 2;
        int y = (td + tu) / 2;
        build(ld(v), tl, x, td, y);
        build(lu(v), tl, x, y + 1, tu);
        build(rd(v), x + 1, tr, td, y);
        build(ru(v), x + 1, tr, y + 1, tu);
        t[v] = t[ld(v)] + t[lu(v)] + t[rd(v)] + t[ru(v)];
    }
    void update(int l, int r, int d, int u, int val, int v = 0, int tl = 1, int tr = N - 1, int td = 1, int tu = N - 1) {
        if (l > r || d > u || tl > tr || td > tu) return;
        if (tr < l || r < tl || tu < d || u < td) return;
        if (!t[v]) return;
        if (l <= tl && tr <= r && d <= td && tu <= u) {
            t[v] = val;
            return;
        }
        int x = (tl + tr) / 2;
        int y = (td + tu) / 2;
        update(l, r, d, u, val, ld(v), tl, x, td, y);
        update(l, r, d, u, val, lu(v), tl, x, y + 1, tu);
        update(l, r, d, u, val, rd(v), x + 1, tr, td, y);
        update(l, r, d, u, val, ru(v), x + 1, tr, y + 1, tu);
        t[v] = t[ld(v)] + t[lu(v)] + t[rd(v)] + t[ru(v)];
    }
    int get(int l, int r, int d, int u, int v = 0, int tl = 1, int tr = N - 1, int td = 1, int tu = N - 1) {
        if (l > r || d > u || tl > tr || td > tu) return 0;
        if (tr < l || r < tl || tu < d || u < td) return 0;
        if (!t[v]) return 0;
        if (l <= tl && tr <= r && d <= td && tu <= u) {
            return t[v];
        }
        int x = (tl + tr) / 2;
        int y = (td + tu) / 2;
        int res = 0;
        res += get(l, r, d, u, ld(v), tl, x, td, y);
        res += get(l, r, d, u, lu(v), tl, x, y + 1, tu);
        res += get(l, r, d, u, rd(v), x + 1, tr, td, y);
        res += get(l, r, d, u, ru(v), x + 1, tr, y + 1, tu);
        return res;
    }
} tree;

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