#include <bits/stdc++.h>

using namespace std;

struct fenwick_tree {
    static const int N = 1e6 + 5;
    int t[N];
    void update(int pos, int val) {
        for (int i = pos; i < N; i = i | (i + 1)) {
            t[i] += val;
        }
    }
    int get_pref_sum(int pref) {
        int res = 0;
        for (int i = pref; i >= 0; i = (i & (i + 1)) - 1) {
            res += t[i];
        }
        return res;
    }
    int get(int l, int r) {
        if (l == 0) return get_pref_sum(r);
        else return get_pref_sum(r) - get_pref_sum(l - 1);
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