#include <bits/stdc++.h>

using namespace std;

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
    used[v] = true;
    dsu.unite(v, root);
    can.erase(v);
    vector<int> tmp;
    for (int to : can) {
        if (!g[v].count(to)) {
            tmp.push_back(to);
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
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL_ALIKHAN
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

#ifdef LOCAL_ALIKHAN
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}