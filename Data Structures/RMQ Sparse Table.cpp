#include <bits/stdc++.h>

using namespace std;

enum TableType { VAL, ARG };

template <typename T, TableType S = TableType::VAL, typename Cmp = less<T>>
struct sparse_table{
    // VAL returns value, ARG returns position of value
    // less<> for minimum, greater<> for maximum
    // d[i][j] = min(a[i], a[i + 1], ... , a[i + (1 << j) - 1])
    // get(l, r) = min(a[l], a[l + 1], ... , a[r])
    static const int N = 1e6 + 10, L = 22;
    T a[N];
    int d[N][L], rem[N];
    void build(int n, Cmp cmp = {}) {
        for (int i = 1; i <= n; i++) { d[i][0] = i; }
        for (int j = 1; j <= L - 1; j++) {
            for (int i = 1; i <= n; i++) {
                if (i + (1 << j) - 1 > n) { continue; }
                d[i][j] = cmp(a[d[i][j - 1]], a[d[i + (1 << (j - 1))][j - 1]]) ? d[i][j - 1] : d[i + (1 << (j - 1))][j - 1];
            }
        }
        for (int i = 1; i <= n; i++) { rem[i] = log2(i); }
    }
    T get(int l, int r, Cmp cmp = {}) {
        int lg = rem[r - l + 1];
        int pos = cmp(a[d[l][lg]], a[d[r - (1 << lg) + 1][lg]]) ? d[l][lg] : d[r - (1 << lg) + 1][lg];
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