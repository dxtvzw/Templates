#include <bits/stdc++.h>

using namespace std;

const int N = 2e3 + 10;
const long long inf = 1e18 + 10;
vector<pair<int, long long>> g[N];
long long dist[N];
bool used[N];
bool low[N];

void dfs(int v) {
    used[v] = true;
    for (auto to : g[v]) {
        if (used[to.first]) continue;
        dfs(to.first);
    }
}

void dfs2(int v) {
    low[v] = true;
    for (auto to : g[v]) {
        if (low[to.first]) continue;
        dfs2(to.first);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL_ALIKHAN
    freopen("input.txt", "r", stdin);
#endif

    int n, m, s;
    cin >> n >> m >> s;
    for (int i = 1; i <= m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
    }
    for (int i = 1; i <= n; i++) {
        dist[i] = inf;
    }
    dfs(s);
    dist[s] = 0;
    for (int kk = 1; kk <= n - 1; kk++) {
        for (int v = 1; v <= n; v++) {
            for (auto edge : g[v]) {
                dist[edge.first] = min(dist[edge.first], dist[v] + edge.second);
            }
        }
    }
    queue<int> q;
    for (int v = 1; v <= n; v++) {
        for (auto edge : g[v]) {
            if (dist[edge.first] > dist[v] + edge.second) {
                dist[edge.first] = dist[v] + edge.second;
                if (used[edge.first]) {
                    q.push(edge.first);
                    low[edge.first] = true;
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

#ifdef LOCAL_ALIKHAN
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}