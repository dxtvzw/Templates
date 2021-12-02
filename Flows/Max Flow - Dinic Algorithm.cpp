#include <bits/stdc++.h>

using namespace std;

typedef long long val_t;

// O(n^2 * m)

const int N = 200 + 10;
const val_t inf = 1e18;

struct Edge {
    int s, e;
    val_t cap, flow;
};

vector<int> g[N];
vector<Edge> edges;
int dist[N], ptr[N];
queue<int> q;

void add_edge(int s, int e, val_t cap) {
    Edge forw = {s, e, cap, 0};
    Edge back = {e, s, 0, 0};
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL_ALIKHAN
    freopen("input.txt", "r", stdin);
#endif


#ifdef LOCAL_ALIKHAN
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}