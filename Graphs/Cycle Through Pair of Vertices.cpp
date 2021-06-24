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

const int N = 1e5 + 10;
vector<int> g[N], t[N + N];
bool used[N + N];
int depth[N], up[N];
int max_col;
vector<pii> edges[N];
int par[N + N];

void dfs1(int v) {
    used[v] = 1;
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
    used[v] = 1;
    for (int to : g[v]) {
        if (depth[to] == depth[v] - 1) {
            continue;
        }
        else if (!used[to]) {
            int nxt = up[to] >= depth[v] ? ++max_col : col;
            edges[nxt].pb({v, to});
            dfs2(to, nxt);
        }
        else if (depth[to] < depth[v]) {
            edges[col].pb({v, to});
        }
    }
}

void dfs3(int v) {
    used[v] = 1;
    for (int to : t[v]) {
        if (!used[to]) {
            par[to] = v;
            dfs3(to);
        }
    }
}

inline bool check(int u, int v) {
    if (u == v) {
        return 1;
    }
    else if (par[u] && par[u] == par[v]) {
        return 1;
    }
    else {
        return par[par[u]] == v || par[par[v]] == u;
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
        g[u].pb(v);
        g[v].pb(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs1(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        used[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs2(i, 0);
        }
    }
    for (int i = 1; i <= max_col; i++) {
        for (auto [u, v] : edges[i]) {
            t[u].pb(i + n);
            t[i + n].pb(u);
            t[v].pb(i + n);
            t[i + n].pb(v);
        }
    }
    for (int i = 1; i <= n; i++) {
        used[i] = 0;
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

#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
