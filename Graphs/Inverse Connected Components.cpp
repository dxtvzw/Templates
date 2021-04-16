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

struct DSU {
    static const int N = 1e6 + 10;
    int Parent[N], Rank[N], cnt;
    void init(const int& n) {
        for (int i = 1; i <= n; i++) {
            Parent[i] = i, Rank[i] = 0;
        }
        cnt = n;
    }
    int find(const int& v) {
        if (Parent[v] == v) return v;
        else return Parent[v] = find(Parent[v]);
    }
    void unite(const int& u, const int& v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        if (Rank[U] < Rank[V]) swap(U, V);
        if (Rank[V] == Rank[U]) Rank[U]++;
        Parent[V] = U, cnt--;
    }
} dsu;

const int N = 2e5 + 10;
set<int> g[N];
set<int> can;
bool used[N];

void dfs(int v, int root) {
    used[v] = 1;
    dsu.unite(v, root);
    can.erase(v);
    vector<int> tmp;
    for (int to : can) {
        if (!g[v].count(to)) {
            tmp.pb(to);
        }
    }
    for (int to : tmp) {
        can.erase(to);
    }
    for (int to : tmp) {
        dfs(to, root);
    }
}

void get_inverse_comps(int n) {
    for (int i = 1; i <= n; i++) {
        can.insert(i);
    }
    dsu.init(n);
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs(i, i);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].insert(v);
        g[v].insert(u);
    }
    get_inverse_comps(n);
    cout << dsu.cnt - 1 << "\n";

#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
