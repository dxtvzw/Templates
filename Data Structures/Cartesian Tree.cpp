#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

struct Node {
    int k, p, id, sz;
    Node *l, *r, *par;
    Node (int k, int p, int id) {
        this->k = k;
        this->p = p;
        this->id = id;
        this->sz = 1;
        this->l = this->r = this->par = nullptr;
    }
};

typedef Node* pNode;
typedef pair<pNode, pNode> ppn;

int sz(pNode t) {
    return t == nullptr ? 0 : t->sz;
}

int k(pNode t) {
    return t == nullptr ? 0 : t->k;
}

int id(pNode t) {
    return t == nullptr ? 0 : t->id;
}

pNode Merge(pNode t1, pNode t2) {
    if (t1 == nullptr) return t2;
    if (t2 == nullptr) return t1;
    pNode res;
    if (t1->p < t2->p) {
        res = t1;
        res->r = Merge(t1->r, t2);
    }
    if (t1->p > t2->p) {
        res = t2;
        res->l = Merge(t1, t2->l);
    }
    res->sz = sz(res->l) + sz(res->r) + 1;
    return res;
}

vector<pNode> Split(pNode t, int k) {
    if (t == nullptr) {
        return {nullptr, nullptr, nullptr};
    }
    else if (t->k == k) {
        pNode q = t;
        q->l = q->r = nullptr;
        return {t->l, q, t->r};
    }
    else if (t->k < k) {
        vector<pNode> nxt = Split(t->r, k);
        t->r = nxt[0];
        return {t, nxt[1], nxt[2]};
    }
    else {
        vector<pNode> nxt = Split(t->l, k);
        t->l = nxt[2];
        return {nxt[0], nxt[1], t};
    }
}

void Insert(pNode &t, pNode nw) {
    vector<pNode> spl = Split(t, nw->k);
    if (spl[1] != nullptr) return;
    t = Merge(Merge(spl[0], nw), spl[2]);
}

struct Kek {
    int a, b, id;
    bool operator<(const Kek& ot) const {
        return a < ot.a;
    }
};

const int N = 5e4 + 10;
Kek v[N];

pNode build(int n) {
    sort(v + 1, v + n + 1);
    vector<pNode> path = {new Node(v[1].a, v[1].b, v[1].id)};
    for (int i = 2; i <= n; i++) {
        pNode last = nullptr;
        while (!path.empty() && path.back()->p > v[i].b) {
            last = path.back();
            path.pop_back();
        }
        pNode cur = new Node(v[i].a, v[i].b, v[i].id);
        cur->l = last;
        if (!path.empty()) {
            path.back()->r = cur;
            cur->par = path.back();
        }
        if (last) {
            last->par = cur;
        }
        path.pb(cur);
    }
    return path[0];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> v[i].a >> v[i].b;
        v[i].id = i;
    }

#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
