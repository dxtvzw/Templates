#include <bits/stdc++.h>

using namespace std;

// segment tree with fractional cascading
// get(l, r, x) = #i: l <= i <= r and x <= a[i]

struct Node {
    int val, lef, rig;
};

struct segment_tree {
    static const int N = 6e5 + 10;
    int a[N];
    vector<Node> t[4 * N];
    vector<Node> merge(const vector<Node>& a, const vector<Node>& b) {
        vector<Node> res;
        int l = 0, r = 0;
        while (l < a.size() && r < b.size()) {
            if (a[l].val <= b[r].val) {
                res.push_back(a[l++]);
            }
            else {
                res.push_back(b[r++]);
            }
        }
        while (l < a.size()) {
            res.push_back(a[l++]);
        }
        while (r < b.size()) {
            res.push_back(b[r++]);
        }
        for (int i = 0, j = 0; i < res.size(); i++) {
            while (j < a.size() && a[j].val < res[i].val) {
                j++;
            }
            res[i].lef = j;
        }
        for (int i = 0, j = 0; i < res.size(); i++) {
            while (j < b.size() && b[j].val < res[i].val) {
                j++;
            }
            res[i].rig = j;
        }
        return res;
    }
    void build(int v = 1, int tl = 1, int tr = N - 1) {
        if (tl > tr) return;
        if (tl == tr) {
            t[v] = {{a[tl], 0, 0}};
            return;
        }
        int tm = (tl + tr) / 2;
        build(v + v, tl, tm);
        build(v + v + 1, tm + 1, tr);
        t[v] = merge(t[v + v], t[v + v + 1]);
    }
    int get_id(int x, int v = 1, int tl = 1, int tr = N - 1) {
        if (t[v].back().val < x) {
            return t[v].size();
        }
        else {
            int lef = 0, rig = t[v].size() - 1;
            while (lef < rig) {
                int mid = (lef + rig) / 2;
                if (t[v][mid].val >= x) {
                    rig = mid;
                }
                else {
                    lef = mid + 1;
                }
            }
            return lef;
        }
    }
    int my_get(int l, int r, int id, int v = 1, int tl = 1, int tr = N - 1) {
        if (tl > tr || l > r || tl > r || l > tr || id == t[v].size()) return 0;
        if (l <= tl && tr <= r) {
            return t[v].size() - id;
        }
        int tm = (tl + tr) / 2;
        return my_get(l, r, t[v][id].lef, v + v, tl, tm) + my_get(l, r, t[v][id].rig, v + v + 1, tm + 1, tr);
    }
    int get(int l, int r, int x, int v = 1, int tl = 1, int tr = N - 1) {
        return my_get(l, r, get_id(x, v, tl, tr), v, tl, tr);
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