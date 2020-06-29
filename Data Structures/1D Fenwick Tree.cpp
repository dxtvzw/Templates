#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

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
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif



#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
