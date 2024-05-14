#include <bits/stdc++.h>

using namespace std;

enum TableType { VAL, ARG };

template <typename T, TableType S = TableType::VAL, typename Cmp = less<T>>
struct sparse_table {
    // VAL returns value, ARG returns position of value
    // less<> for minimum, greater<> for maximum
    // d[i][j] = min(a[i], a[i + 1], ... , a[i + (1 << j) - 1])
    // get(l, r) = min(a[l], a[l + 1], ... , a[r])
    static const int N = 1e6 + 10, L = 21;
    T a[N];
    int d[L][N];
    void build(int n, Cmp cmp = {}) {
        for (int i = 1; i <= n; i++) { d[0][i] = i; }
        for (int j = 1; j <= L - 1; j++) {
            for (int i = 1; i <= n; i++) {
                if (i + (1 << j) - 1 > n) { continue; }
                d[j][i] = cmp(a[d[j - 1][i]], a[d[j - 1][i + (1 << (j - 1))]]) ? d[j - 1][i] : d[j - 1][i + (1 << (j - 1))];
            }
        }
    }
    T get(int l, int r, Cmp cmp = {}) {
        int lg = __lg(r - l + 1);
        int pos = cmp(a[d[lg][l]], a[d[lg][r - (1 << lg) + 1]]) ? d[lg][l] : d[lg][r - (1 << lg) + 1];
        if constexpr (S == TableType::VAL) { return a[pos]; } else { return pos; }
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