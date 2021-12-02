#include <bits/stdc++.h>

using namespace std;

typedef complex<long long> point;
#define x real
#define y imag

const int N = 1e5 + 10;
const long long inf = 1e18;
const point init_line = {0, inf};

struct Node {
    int l, r;
    Node *lef, *rig;
    point line;
    Node(int L = -N, int R = N) {
        l = L, r = R;
        lef = nullptr, rig = nullptr;
        line = init_line;
    }
};

long long dot(point a, point b) {
    return (conj(a) * b).x();
}

long long f(point a, long long x) {
    return dot(a, {x, 1});
}

point line[4 * N];
Node *root[N];

void build() {
    for (int i = 0; i < 4 * N; i++) line[i] = {0, inf};
}

void add_line(point nw, Node *v) {
    if (f(nw, v->l) >= f(v->line, v->l) && f(nw, v->r) >= f(v->line, v->r)) return;
    int m = (v->l + v->r) / 2;
    bool lef = f(nw, v->l) < f(v->line, v->l);
    bool mid = f(nw, m) < f(v->line, m);
    if (mid) swap(v->line, nw);
    if (v->l + 1 == v->r) return;
    else if (lef != mid) {
        if (v->lef == nullptr) v->lef = new Node(v->l, m);
        add_line(nw, v->lef);
    }
    else {
        if (v->rig == nullptr) v->rig = new Node(m, v->r);
        add_line(nw, v->rig);
    }
}

long long get(int x, Node *v) {
    int m = (v->l + v->r) / 2;
    if (v->l + 1 == v->r) return f(v->line, x);
    else if (x < m) {
        if (v->lef == nullptr) return f(v->line, x);
        else return min(f(v->line, x), get(x, v->lef));
    }
    else {
        if (v->rig == nullptr) return f(v->line, x);
        else return min(f(v->line, x), get(x, v->rig));
    }
}

void merge(Node *v, Node *u) {
    add_line(u->line, v);
    if (u->lef != nullptr) merge(v, u->lef);
    if (u->rig != nullptr) merge(v, u->rig);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL_ALIKHAN
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        root[i] = new Node();
    }

#ifdef LOCAL_ALIKHAN
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}