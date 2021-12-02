#include <bits/stdc++.h>

using namespace std;

typedef long long val_t;

const int N = 500 + 10;
const val_t inf = 1e18;

struct Edge {
    int s, e;
    val_t cap, flow;
    int id;
};

vector<int> g[N];
vector<Edge> edges;
int dist[N], ptr[N];
queue<int> q;
bool used[N];
int par[N];
vector<int> path;
vector<vector<int>> ans;

void add_edge(int s, int e, val_t cap, int id) {
    Edge forw = {s, e, cap, 0, id};
    Edge back = {e, s, 0, 0, -id};
    g[s].push_back(edges.size());
    edges.push_back(forw);
    g[e].push_back(edges.size());
    edges.push_back(back);
}

bool bfs(int src, int sink) {
    while (!q.empty()) q.pop();
    q.push(src);
    for (int i = 0; i < N; i++) dist[i] = -1;
    dist[src] = 0;
    while (!q.empty() && dist[sink] == -1) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < g[v].size(); i++) {
            int id = g[v][i];
            int u = edges[id].e;
            if (dist[u] == -1 && edges[id].flow < edges[id].cap) {
                q.push(u);
                dist[u] = dist[v] + 1;
            }
        }
    }
    return dist[sink] != -1;
}

val_t dfs(int v, val_t flow, int sink) {
    if (!flow) return 0;
    if (v == sink) return flow;
    while (ptr[v] < g[v].size()) {
        int id = g[v][ptr[v]];
        int u = edges[id].e;
        if (dist[u] != dist[v] + 1) {
            ptr[v]++;
            continue;
        }
        val_t pushed = dfs(u, min(flow, edges[id].cap - edges[id].flow), sink);
        if (pushed) {
            edges[id].flow += pushed;
            edges[id ^ 1].flow -= pushed;
            return pushed;
        }
        ptr[v]++;
    }
    return 0;
}

val_t max_flow(int src, int sink) {
    val_t flow = 0;
    while (true) {
        if (!bfs(src, sink)) break;
        for (int i = 0; i < N; i++) ptr[i] = 0;
        while (val_t pushed = dfs(src, inf, sink)) {
            flow += pushed;
        }
    }
    return flow;
}

void dfs1(int v) {
    used[v] = true;
    for (int id : g[v]) {
        int to = edges[id].e;
        if (edges[id].id > 0 && edges[id].flow > 0 && !used[to]) {
            par[to] = id;
            dfs1(to);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL_ALIKHAN
    freopen("input.txt", "r", stdin);
#endif

    // find decomposition of max flow in directed graph
    // output format: flow, number of edges, edges' ids
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w, i);
    }
    max_flow(1, n);
    while (true) {
        for (int i = 1; i <= n; i++) {
            used[i] = false;
            par[i] = 0;
        }
        dfs1(1);
        if (!used[n]) {
            break;
        }
        int v = n;
        path.clear();
        while (v > 1) {
            path.push_back(par[v]);
            v = edges[par[v]].s;
        }
        reverse(path.begin(), path.end());
        val_t mn = 1e10; // change to maximal capacity through an edge
        for (int id : path) {
            mn = min(mn, edges[id].flow);
        }
        vector<int> cur;
        cur.push_back(mn);
        cur.push_back(path.size());
        for (int id : path) {
            cur.push_back({edges[id].id});
            edges[id].flow -= mn;
        }
        ans.push_back(cur);
    }
    cout << ans.size() << "\n";
    for (const auto& it : ans) {
        for (int i : it) {
            cout << i << " ";
        }
        cout << "\n";
    }

#ifdef LOCAL_ALIKHAN
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}