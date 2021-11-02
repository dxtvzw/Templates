#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128_t LL;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define F first
#define S second
#define pb push_back
mt19937 rnd(time(0));

using val_type = int;                                //////////////////// CHANGE
using range_type = int;                                    //////////////////// CHANGE

const val_type inf = numeric_limits<val_type>::max() / 2;
const val_type val_init = 0;                               //////////////////// CHANGE
const val_type carry_init = 0;                             //////////////////// CHANGE

val_type merge(const val_type& a, const val_type& b) {
    return max(a, b);                                          //////////////////// CHANGE
}

void modify_carry(val_type& a, const val_type& b) {
    a += b;                                                 //////////////////// CHANGE
}

struct Node;

using pNode = shared_ptr<Node>;

struct Node {
    val_type val = val_init;
    val_type carry = carry_init;
    range_type tl, tr;
    pNode lef, rig;
    inline static int node_counter = 0;
    Node(const val_type& val, range_type tl, range_type tr) : val(val), tl(tl), tr(tr) {
        node_counter++;
    }
    ~Node() {
        node_counter--;
    }
};

pNode CreateNode(const val_type& val, range_type tl, range_type tr) {
    return make_shared<Node>(val, tl, tr);
}

pNode CreateNode(range_type tl, range_type tr) {
    return make_shared<Node>(val_init, tl, tr);
}

ostream& operator<<(ostream& ostr, const Node& t) {
    return ostr << t.tl << " " << t.tr << " " << t.val << " " << t.carry;
}

ostream& operator<<(ostream& ostr, pNode t) {
    return ostr << *t;
}

pNode lef(pNode t) {
    return t->lef ? t->lef : t->lef = CreateNode(t->tl, (t->tl + t->tr) / 2);
}

pNode rig(pNode t) {
    return t->rig ? t->rig : t->rig = CreateNode((t->tl + t->tr) / 2 + 1, t->tr);
}

void push(pNode t) {
    if (t->carry == carry_init) {
        return;
    }
    else {
        t->val += t->carry;           //////////////////// CHANGE
        if (t->tl < t->tr) {
            modify_carry(lef(t)->carry, t->carry);
            modify_carry(rig(t)->carry, t->carry);
        }
        t->carry = carry_init;
    }
}

void recalc(pNode t) {
    t->val = val_init;
    if (t->lef) {
        t->val = merge(t->val, lef(t)->val);
    }
    if (t->rig) {
        t->val = merge(t->val, rig(t)->val);
    }
}

void update(pNode t, range_type l, range_type r, const val_type& val) {
    push(t);
    if (t->tr < l || r < t->tl) {
        return;
    }
    else if (l <= t->tl && t->tr <= r) {
        modify_carry(t->carry, val);
        push(t);
    }
    else {
        update(lef(t), l, r, val);
        update(rig(t), l, r, val);
        recalc(t);
    }
}

val_type get(pNode t, range_type l, range_type r) {
    push(t);
    if (t->tr < l || r < t->tl) {
        return val_init;
    }
    else if (l <= t->tl && t->tr <= r) {
        return t->val;
    }
    else {
        val_type res = val_init;
        if (t->lef) {
            res = merge(res, get(lef(t), l, r));
        }
        if (t->rig) {
            res = merge(res, get(rig(t), l, r));
        }
        recalc(t);
        return res;
    }
}

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
