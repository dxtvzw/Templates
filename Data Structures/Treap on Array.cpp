#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

template<int mod>
class Modular {
public:
    int val;
    Modular() : val(0) {}
    Modular(int new_val) : val(new_val) {
    }
    friend Modular operator+(const Modular& a, const Modular& b) {
        if (a.val + b.val >= mod) return a.val + b.val - mod;
        else return a.val + b.val;
    }
    friend Modular operator-(const Modular& a, const Modular& b) {
        if (a.val - b.val < 0) return a.val - b.val + mod;
        else return a.val - b.val;
    }
    friend Modular operator*(const Modular& a, const Modular& b) {
        return 1ll * a.val * b.val % mod;
    }
    friend Modular binpow(Modular a, long long n) {
        Modular res = 1;
        for (; n; n >>= 1) {
            if (n & 1) res *= a;
            a *= a;
        }
        return res;
    }
    /* ALTERNATIVE INVERSE FUNCTION USING EXTENDED EUCLIDEAN ALGORITHM
    friend void gcd(int a, int b, Modular& x, Modular& y) {
        if (a == 0) {
            x = Modular(0);
            y = Modular(1);
            return;
        }
        Modular x1, y1;
        gcd(b % a, a, x1, y1);
        x = y1 - (b / a) * x1;
        y = x1;
    }
    friend Modular inv(const Modular& a) {
        Modular x, y;
        gcd(a.val, mod, x, y);
        return x;
    }
    */
    friend Modular inv(const Modular& a) {
        return binpow(a, mod - 2);
    }
    Modular operator/(const Modular& ot) const {
        return *this * inv(ot);
    }
    Modular& operator++() {
        if (val + 1 == mod) val = 0;
        else ++val;
        return *this;
    }
    Modular operator++(int) {
        Modular tmp = *this;
        ++(*this);
        return tmp;
    }
    Modular operator+() const {
        return *this;
    }
    Modular operator-() const {
        return 0 - *this;
    }
    Modular& operator+=(const Modular& ot) {
        return *this = *this + ot;
    }
    Modular& operator-=(const Modular& ot) {
        return *this = *this - ot;
    }
    Modular& operator*=(const Modular& ot) {
        return *this = *this * ot;
    }
    Modular& operator/=(const Modular& ot) {
        return *this = *this / ot;
    }
    bool operator==(const Modular& ot) const {
        return val == ot.val;
    }
    bool operator!=(const Modular& ot) const {
        return val != ot.val;
    }
    bool operator<(const Modular& ot) const {
        return val < ot.val;
    }
    bool operator>(const Modular& ot) const {
        return val > ot.val;
    }
    explicit operator int() const {
        return val;
    }
};

template<int mod>
istream& operator>>(istream& istr, Modular<mod>& x) {
    return istr >> x.val;
}

template<int mod>
ostream& operator<<(ostream& ostr, const Modular<mod>& x) {
    return ostr << x.val;
}

const int mod = 998244353; // 998244353
using Mint = Modular<mod>;

std::mt19937 rnd;

struct Node {
    Mint val, ch;
    int prio, sz;
    int l, r;
    Node (Mint _val = 0) {
        val = _val;
        ch = 1;
        prio = rnd();
        sz = 1;
        l = 0;
        r = 0;
    }
};

const int T = 4e6 + 10;
int node_ptr = 0;
Node nodes[T];

int new_node(Mint val = 0) {
    nodes[++node_ptr] = Node(val);
    return node_ptr;
}

int sz(int t) {
    return t == 0 ? 0 : nodes[t].sz;
}

Mint val(int t) {
    return t == 0 ? 0 : nodes[t].val;
}

void push(int t) {
    if (!t) return;
    nodes[t].val *= nodes[t].ch;
    if (nodes[t].l) {
        nodes[nodes[t].l].ch *= nodes[t].ch;
    }
    if (nodes[t].r) {
        nodes[nodes[t].r].ch *= nodes[t].ch;
    }
    nodes[t].ch = 1;
}

void recalc(int t) {
    if (!t) return;
    push(nodes[t].l);
    push(nodes[t].r);
    nodes[t].sz = sz(nodes[t].l) + sz(nodes[t].r) + 1;
}

int Merge(int t1, int t2) {
    push(t1);
    push(t2);
    if (t1 == 0) return t2;
    if (t2 == 0) return t1;
    int res = 0;
    if (nodes[t1].prio < nodes[t2].prio) {
        res = t1;
        nodes[res].r = Merge(nodes[t1].r, t2);
    }
    else {
        res = t2;
        nodes[res].l = Merge(t1, nodes[t2].l);
    }
    recalc(res);
    return res;
}

pair<int, int> Split_pref(int t, int k) {
    push(t);
    if (sz(t) <= k) {
        return {t, 0};
    }
    else if (sz(nodes[t].l) + 1 <= k) {
        pair<int, int> nxt = Split_pref(nodes[t].r, k - sz(nodes[t].l) - 1);
        nodes[t].r = nxt.first;
        recalc(t);
        return {t, nxt.second};
    }
    else {
        pair<int, int> nxt = Split_pref(nodes[t].l, k);
        nodes[t].l = nxt.second;
        recalc(t);
        return {nxt.first, t};
    }
}

pair<int, int> Split(int t, int lef, int rig) {
    pair<int, int> a = Split_pref(t, lef - 1);
    pair<int, int> b = Split_pref(a.second, rig - lef + 1);
    return {b.first, Merge(a.first, b.second)};
}

vector<int> Split_in_three(int t, int lef, int rig) {
    pair<int, int> a = Split_pref(t, lef - 1);
    pair<int, int> b = Split_pref(a.second, rig - lef + 1);
    return {a.first, b.first, b.second};
}

void dfs_print(int v) {
    push(v);
    if (v == 0) return;
    if (nodes[v].l) dfs_print(nodes[v].l);
    cout << val(v) << " ";
    if (nodes[v].r) dfs_print(nodes[v].r);
}

void dfs_get(int v, vector<Mint>& vec) {
    push(v);
    if (v == 0) return;
    if (nodes[v].l) dfs_get(nodes[v].l, vec);
    vec.push_back(val(v));
    if (nodes[v].r) dfs_get(nodes[v].r, vec);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif



#ifdef LOCAL
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
}