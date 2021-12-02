#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
vector<int> g[N], t[N + N];
bool used[N + N];
int depth[N], up[N];
int max_col;
vector<pair<int, int>> edges[N];
int par[N + N];

void dfs1(int v) {
    used[v] = true;
    up[v] = depth[v];
    for (int to : g[v]) {
        if (!used[to]) {
            depth[to] = depth[v] + 1;
            dfs1(to);
            up[v] = min(up[v], up[to]);
        }
        else {
            up[v] = min(up[v], depth[to]);
        }
    }
}

void dfs2(int v, int col) {
    used[v] = true;
    for (int to : g[v]) {
        if (depth[to] == depth[v] - 1) {
            continue;
        }
        else if (!used[to]) {
            int nxt = up[to] >= depth[v] ? ++max_col : col;
            edges[nxt].emplace_back(v, to);
            dfs2(to, nxt);
        }
        else if (depth[to] < depth[v]) {
            edges[col].emplace_back(v, to);
        }
    }
}

void dfs3(int v) {
    used[v] = true;
    for (int to : t[v]) {
        if (!used[to]) {
            par[to] = v;
            dfs3(to);
        }
    }
}

bool check(int u, int v) {
    if (u == v) {
        return true;
    }
    else if (par[u] && par[u] == par[v]) {
        return true;
    }
    else {
        return par[par[u]] == v || par[par[v]] == u;
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
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs1(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        used[i] = false;
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs2(i, 0);
        }
    }
    for (int i = 1; i <= max_col; i++) {
        for (auto [u, v] : edges[i]) {
            t[u].push_back(i + n);
            t[i + n].push_back(u);
            t[v].push_back(i + n);
            t[i + n].push_back(v);
        }
    }
    for (int i = 1; i <= n; i++) {
        used[i] = false;
    }
    for (int i = 1; i <= n; i++) {
        if (!par[i]) {
            dfs3(i);
        }
    }
    int q, a, b;
    cin >> q >> a >> b;
    int ans = 0;
    while (q--) {
        ans += check(a, b);
        int tmp = (1ll * 13579 * a + 1ll * 97531 * b) % n + 1;
        a = b;
        b = tmp;
    }
    cout << ans << "\n";

#ifdef LOCAL_ALIKHAN
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}