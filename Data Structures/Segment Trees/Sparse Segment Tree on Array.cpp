#include <bits/stdc++.h>

using namespace std;

/*
    tested on:
        https://codeforces.com/gym/103091/problem/G

    FIX MIDDLE TM = (TL + TR) / 2 (TL = -1, TR = 0 RESULTS IN INFINITE LOOP)
*/

template <typename Value, typename Range>
class SparseSegmentTree {
private:
    static const Value val_inf = numeric_limits<Value>::max() / 2 - 10;
    static const Value val_init = 0;                               //////////////////// CHANGE
    static const Value lazy_init = 0;                             //////////////////// CHANGE

    static const Range range_inf = numeric_limits<Range>::max() / 2 - 10;
    static const Range LB = -range_inf;                  //////////////////// CHANGE
    static const Range RB = range_inf;                  //////////////////// CHANGE

    Value merge(const Value& a, const Value& b) const {
        return max(a, b);                                          //////////////////// CHANGE
    }

    void modify_lazy(Value& a, const Value& b) {
        a += b;                                                 //////////////////// CHANGE
    }

    struct Node {
        Value val = val_init;
        Value lazy = lazy_init;
        int lef = 0;
        int rig = 0;
        Node() {
        }
        Node(const Value& val) : val(val) {
        }
    };

    static const int N = 1e7; // this is fine for real Q <= 1e5
    Node tree[N];
    int node_counter = 1; // tree[1] -- root

    int lef(int t) {
        return tree[t].lef ? tree[t].lef : tree[t].lef = ++node_counter;
    }

    int rig(int t) {
        return tree[t].rig ? tree[t].rig : tree[t].rig = ++node_counter;
    }

    void push(int t, Range tl, Range tr) {
        if (tree[t].lazy == lazy_init) {
            return;
        }
        else {
            tree[t].val += tree[t].lazy;           //////////////////// CHANGE
            if (tl < tr) {
                modify_lazy(tree[lef(t)].lazy, tree[t].lazy);
                modify_lazy(tree[rig(t)].lazy, tree[t].lazy);
            }
            tree[t].lazy = lazy_init;
        }
    }

public:
    void update(Range l, Range r, const Value& val, int t = 1, Range tl = LB, Range tr = RB) {
        push(t, tl, tr);
        if (tr < l || r < tl) {
            return;
        }
        else if (l <= tl && tr <= r) {
            modify_lazy(tree[t].lazy, val);
            push(t, tl, tr);
        }
        else {
            Range tm = (tl + tr) / 2;
            update(l, r, val, lef(t), tl, tm);
            update(l, r, val, rig(t), tm + 1, tr);
            tree[t].val = merge(tree[tree[t].lef].val, tree[tree[t].rig].val);
        }
    }

    Value get(Range l, Range r, int t = 1, Range tl = LB, Range tr = RB) {
        push(t, tl, tr);
        if (tr < l || r < tl) {
            return val_init;
        }
        else if (l <= tl && tr <= r) {
            return tree[t].val;
        }
        else {
            Value res = val_init;
            Range tm = (tl + tr) / 2;
            if (tree[t].lef) {
                res = merge(res, get(l, r, tree[t].lef, tl, tm));
            }
            if (tree[t].rig) {
                res = merge(res, get(l, r, tree[t].rig, tm + 1, tr));
            }
            return res;
        }
    }
};

SparseSegmentTree<int, int> tree;

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