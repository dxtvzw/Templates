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

const int N = 500 + 10;
const ll inf = 1e18;

struct Edge {
    int s, e;
    ll cap, flow;
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

void add_edge(int s, int e, ll cap, int id) {
    Edge forw = {s, e, cap, 0, id};
    Edge back = {e, s, 0, 0, -id};
    g[s].pb(edges.size());
    edges.pb(forw);
    g[e].pb(edges.size());
    edges.pb(back);
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

ll dfs(int v, ll flow, int sink) {
    if (!flow) return 0;
    if (v == sink) return flow;
    while (ptr[v] < g[v].size()) {
        int id = g[v][ptr[v]];
        int u = edges[id].e;
        if (dist[u] != dist[v] + 1) {
            ptr[v]++;
            continue;
        }
        ll pushed = dfs(u, min(flow, edges[id].cap - edges[id].flow), sink);
        if (pushed) {
            edges[id].flow += pushed;
            edges[id ^ 1].flow -= pushed;
            return pushed;
        }
        ptr[v]++;
    }
    return 0;
}

ll max_flow(int src, int sink) {
    ll flow = 0;
    while (1) {
        if (!bfs(src, sink)) break;
        for (int i = 0; i < N; i++) ptr[i] = 0;
        while (ll pushed = dfs(src, inf, sink)) {
            flow += pushed;
        }
    }
    return flow;
}

void dfs1(int v) {
    used[v] = 1;
    for (int id : g[v]) {
        int to = edges[id].e;
        if (edges[id].id > 0 && edges[id].flow > 0 && !used[to]) {
            par[to] = id;
            dfs1(to);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
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
    while (1) {
        for (int i = 1; i <= n; i++) {
            used[i] = 0;
            par[i] = 0;
        }
        dfs1(1);
        if (!used[n]) {
            break;
        }
        int v = n;
        path.clear();
        while (v > 1) {
            path.pb(par[v]);
            v = edges[par[v]].s;
        }
        reverse(path.begin(), path.end());
        ll mn = 1e10; // change to maximal capacity through an edge
        for (int id : path) {
            mn = min(mn, edges[id].flow);
        }
        vector<int> cur;
        cur.pb(mn);
        cur.pb(path.size());
        for (int id : path) {
            cur.pb({edges[id].id});
            edges[id].flow -= mn;
        }
        ans.pb(cur);
    }
    cout << ans.size() << "\n";
    for (const auto& it : ans) {
        for (int i : it) {
            cout << i << " ";
        }
        cout << "\n";
    }

#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
