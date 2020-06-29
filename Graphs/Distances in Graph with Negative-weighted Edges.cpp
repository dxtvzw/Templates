#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

const int N = 2e3 + 10;
const ll inf = 1e18 + 10;
vector<pair<int, ll>> g[N];
ll dist[N];
bool used[N];
bool low[N];

void dfs(int v) {
    used[v] = 1;
    for (auto to : g[v]) {
        if (used[to.F]) continue;
        dfs(to.F);
    }
    return;
}

void dfs2(int v) {
    low[v] = 1;
    for (auto to : g[v]) {
        if (low[to.F]) continue;
        dfs2(to.F);
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    int n, m, s;
    cin >> n >> m >> s;
    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        g[u].pb({v, w});
    }
    for (int i = 1; i <= n; i++) {
        dist[i] = inf;
    }
    dfs(s);
    dist[s] = 0;
    for (int kk = 1; kk <= n - 1; kk++) {
        for (int v = 1; v <= n; v++) {
            for (auto edge : g[v]) {
                dist[edge.F] = min(dist[edge.F], dist[v] + edge.S);
            }
        }
    }
    queue<int> q;
    for (int v = 1; v <= n; v++) {
        for (auto edge : g[v]) {
            if (dist[edge.F] > dist[v] + edge.S) {
                dist[edge.F] = dist[v] + edge.S;
                if (used[edge.F]) {
                    q.push(edge.F);
                    low[edge.F] = 1;
                }
            }
        }
    }
    while (!q.empty()) {
        dfs2(q.front());
        q.pop();
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            cout << '*' << '\n';
        }
        else if (low[i]) {
            cout << '-' << '\n';
        }
        else {
            cout << dist[i] << '\n';
        }
    }

#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
