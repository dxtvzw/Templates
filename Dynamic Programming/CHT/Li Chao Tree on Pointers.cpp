#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

typedef complex<ll> point;
#define x real
#define y imag

const int N = 1e5 + 10;
const ll inf = 1e18;
const point init_line = {0, inf};

struct Node {
    int l, r;
    Node *lef, *rig;
    point line;
    Node(int L = -N, int R = N) {
        l = L, r = R;
        lef = NULL, rig = NULL;
        line = init_line;
    }
};

ll dot(point a, point b) {
    return (conj(a) * b).x();
}

ll f(point a, ll x) {
    return dot(a, {x, 1});
}

point line[4*N];
Node *root[N];

void build() {
    for (int i=0; i<4*N; i++) line[i] = {0, inf};
}

void add_line(point nw, Node *v) {
    if (f(nw, v->l) >= f(v->line, v->l) && f(nw, v->r) >= f(v->line, v->r)) return;
    int m = (v->l + v->r) / 2;
    bool lef = f(nw, v->l) < f(v->line, v->l);
    bool mid = f(nw, m) < f(v->line, m);
    if (mid) swap(v->line, nw);
    if (v->l + 1 == v->r) return;
    else if (lef != mid) {
        if (v->lef == NULL) v->lef = new Node(v->l, m);
        add_line(nw, v->lef);
    }
    else {
        if (v->rig == NULL) v->rig = new Node(m, v->r);
        add_line(nw, v->rig);
    }
}

ll get(int x, Node *v) {
    int m = (v->l + v->r) / 2;
    if (v->l + 1 == v->r) return f(v->line, x);
    else if (x < m) {
        if (v->lef == NULL) return f(v->line, x);
        else return min(f(v->line, x), get(x, v->lef));
    }
    else {
        if (v->rig == NULL) return f(v->line, x);
        else return min(f(v->line, x), get(x, v->rig));
    }
}

void merge(Node *v, Node *u) {
    add_line(u->line, v);
    if (u->lef != NULL) merge(v, u->lef);
    if (u->rig != NULL) merge(v, u->rig);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;
    for (int i=1; i<=n; i++) {
        root[i] = new Node();
    }

#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
