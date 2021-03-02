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
mt19937 rnd;

struct Node {
    int val, sum, sz;
    Node *l, *r;
    Node (int _val) {
        val = _val;
        sum = _val;
        sz = 1;
        l = nullptr;
        r = nullptr;
    }
};

typedef Node* pNode;
typedef pair<pNode, pNode> ppn;

int sz(pNode t) {
    return t == nullptr ? 0 : t->sz;
}

int val(pNode t) {
    return t == nullptr ? 0 : t->val;
}

int sum(pNode t) {
    return t == nullptr ? 0 : t->sum;
}

void recalc(pNode t) {
    if (!t) return;
    t->sz = sz(t->l) + sz(t->r) + 1;
    t->sum = sum(t->l) + sum(t->r) + val(t);
}

pNode Copy(pNode v) {
    if (!v) return v;
    pNode res = new Node(val(v));
    res->l = v->l;
    res->r = v->r;
    recalc(res);
    return res;
}

pNode Merge(pNode t1, pNode t2) {
    if (t1 == nullptr) return t2;
    if (t2 == nullptr) return t1;
    pNode res;
    if (rnd() % (t1->sz + t2->sz) + 1 <= t1->sz) {
        res = Copy(t1);
        res->r = Merge(t1->r, t2);
    }
    else {
        res = Copy(t2);
        res->l = Merge(t1, t2->l);
    }
    recalc(res);
    return res;
}

ppn Split_pref(pNode t, int k) {
    if (sz(t) <= k) {
        return {t, nullptr};
    }
    else if (sz(t->l) + 1 <= k) {
        ppn nxt = Split_pref(t->r, k - sz(t->l) - 1);
        pNode res = Copy(t);
        res->r = nxt.F;
        recalc(res);
        return {res, nxt.S};
    }
    else {
        ppn nxt = Split_pref(t->l, k);
        pNode res = Copy(t);
        res->l = nxt.S;
        recalc(res);
        return {nxt.F, res};
    }
}

ppn Split(pNode t, int lef, int rig) {
    ppn a = Split_pref(t, lef - 1);
    ppn b = Split_pref(a.S, rig - lef + 1);
    return {b.F, Merge(a.F, b.S)};
}

vector<pNode> Split_in_three(pNode t, int lef, int rig) {
    ppn a = Split_pref(t, lef - 1);
    ppn b = Split_pref(a.S, rig - lef + 1);
    return {a.F, b.F, b.S};
}

int get_sum(pNode& t, int lef, int rig) {
    ppn a = Split_pref(t, lef - 1);
    ppn b = Split_pref(a.S, rig - lef + 1);
    int ans = sum(b.F);
    t = Merge(a.F, Merge(b.F, b.S));
    return ans;
}

void dfs_print(pNode v) {
    if (v == nullptr) return;
    if (v->l) dfs_print(v->l);
    cout << val(v) << " ";
    if (v->r) dfs_print(v->r);
}

void dfs_delete(pNode v) {
    if (v == nullptr) return;
    dfs_delete(v->l);
    dfs_delete(v->r);
    delete v;
}

const int N = 2e5 + 10;
pNode roots[N];

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
