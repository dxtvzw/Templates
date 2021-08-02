#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

struct Edge {
    int to;
    ll flow, cap, cost;
    int rev;
};

const int N = 200 + 10;
const ll inf = 1e18;
vector<Edge> g[N];
int prev_edge[N], prev_vert[N];
ll prio[N], cur_flow[N], dist[N];
queue<int> q;
bool in_queue[N];

void add_edge(int s, int e, ll cap, ll cost) {
    Edge forw = {e, 0, cap, cost, int(g[e].size())};
    Edge back = {s, 0, 0, -cost, int(g[s].size())};
    g[s].pb(forw);
    g[e].pb(back);
}

void SPFA(int s) {
    for (int i = 0; i < N; i++) {
        dist[i] = inf;
    }
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        in_queue[v] = 0;
        for (int i = 0; i < g[v].size(); i++) {
            Edge& e = g[v][i];
            if (e.cap <= e.flow) continue;
            int u = e.to;
            if (dist[u] > dist[v] + e.cost) {
                dist[u] = dist[v] + e.cost;
                if (!in_queue[u]) {
                    in_queue[u] = 1;
                    q.push(u);
                }
            }
        }
    }
}

pair<ll, ll> min_cost_flow(int src, int sink, ll max_flow = inf) {
    SPFA(src); //SPFA is not needed if all edge costs are non-negative
    ll flow = 0, cost = 0;
    while (flow < max_flow) {
        priority_queue<ll> pq;
        pq.push(src);
        for (int i = 0; i < N; i++) {
            prio[i] = inf;
        }
        prio[src] = 0;
        cur_flow[src] = inf;
        while (!pq.empty()) {
            ll v = pq.top();
            pq.pop();
            if ((v >> 32) != prio[v]) continue;
            for (int i = 0; i < g[v].size(); i++) {
                Edge& e = g[v][i];
                int u = e.to;
                if (e.cap <= e.flow) continue;
                if (prio[u] > prio[v] + e.cost + dist[v] - dist[u]) {
                    prio[u] = prio[v] + e.cost + dist[v] - dist[u];
                    pq.push((prio[u] << 32) + u);
                    prev_vert[u] = v;
                    prev_edge[u] = i;
                    cur_flow[u] = min(cur_flow[v], e.cap - e.flow);
                }
            }
        }
        if (prio[sink] == inf) break;
        for (int i = 0; i < N; i++) {
            dist[i] += prio[i];
        }
        ll pushed = min(cur_flow[sink], max_flow - flow);
        flow += pushed;
        int v = sink;
        while (v != src) {
            Edge& e = g[prev_vert[v]][prev_edge[v]];
            e.flow += pushed;
            g[v][e.rev].flow -= pushed;
            cost += pushed * e.cost;
            v = prev_vert[v];
        }
    }
    return {flow, cost};
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif



#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
