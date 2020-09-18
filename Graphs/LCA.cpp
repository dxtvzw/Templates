#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

const int N = 1e5 + 10;
const int L = 20;
vector<int> g[N];
int in[N], out[N];
int up[N][L];
int timer;
int depth[N];

void dfs_lca(int v = 1, int p = 1) {
    in[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i < L; i++) {
        up[v][i] = up[up[v][i-1]][i-1];
    }
    for (int to : g[v]) {
        if (to != p) {
            depth[to] = depth[v] + 1;
            dfs_lca(to, v);
        }
    }
    out[v] = ++timer;
}

bool is_anc(int u, int v) {
    return in[u] <= in[v] && in[v] <= out[u];
}

int lca(int u, int v) {
    if (is_anc(u, v)) return u;
    else if (is_anc(v, u)) return v;
    for (int i = L - 1; i >= 0; i--) {
        if (!is_anc(up[u][i], v)) u = up[u][i];
    }
    return up[u][0];
}

int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    dfs_lca();

#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
