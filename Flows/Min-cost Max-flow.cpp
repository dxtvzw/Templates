#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct MCMF {
    struct edge {
        int to, rev;
        T cap, cost;
    };
    const T inf = numeric_limits<T>::max() / 2;
    int n;
    vector<vector<edge>> g;
    vector<T> phi, dist;
    vector<int> ptr;
    vector<bool> inque, used;
    queue<int> que;
    priority_queue<pair<T, int>, vector<pair<T, int> >, greater<pair<T, int> > > pq;
    MCMF(int _n) : n(_n), g(_n), phi(_n), dist(_n), inque(_n), ptr(_n), used(_n) {
    }
    void add_edge(int s, int t, T cap, T cost) {
        g[s].push_back({t, (int) g[t].size(), cap, cost});
        g[t].push_back({s, (int) g[s].size() - 1, 0, -cost});
    }
    void prep(int src, int sink) {
        fill(phi.begin(), phi.end(), inf);
        fill(dist.begin(), dist.end(), inf);
        que.push(src);
        inque[src] = true;
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            inque[v] = false;
            for (auto& e : g[v]) {
                if (e.cap > 0 && phi[e.to] > phi[v] + e.cost) {
                    phi[e.to] = phi[v] + e.cost;
                    if (!inque[e.to]) {
                        que.push(e.to);
                        inque[e.to] = 1;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (auto& e : g[i]) {
                if (e.cap > 0) {
                    e.cost += phi[i] - phi[e.to];
                }
            }
        }
        pq.emplace(0, src);
        dist[src] = 0;
        while (!pq.empty()) {
            auto [val, v] = pq.top();
            pq.pop();
            if (dist[v] != val) continue;
            for (auto& e : g[v]) {
                if (e.cap > 0 && dist[e.to] > val + e.cost) {
                    dist[e.to] = val + e.cost;
                    pq.emplace(dist[e.to], e.to);
                }
            }
        }
    }
    T dfs(int v, int sink, T flow) {
        used[v] = true;
        if (v == sink) return flow;
        for (; ptr[v] < g[v].size(); ptr[v]++) {
            auto &e = g[v][ptr[v]];
            if (!used[e.to] && dist[e.to] == e.cost + dist[v] && e.cap > 0) {
                T res = dfs(e.to, sink, min(e.cap, flow));
                if (res != 0) {
                    e.cap -= res;
                    g[e.to][e.rev].cap += res;
                    return res;
                }
            }
        }
        return 0;
    }
    pair<T, T> match(int src, int sink) {
        prep(src, sink);
        for (int i = 0; i < n; i++) {
            dist[i] += phi[sink] - phi[src];
        }
        T flow = 0, cost = 0;
        while (true) {
            fill(ptr.begin(), ptr.end(), 0);
            fill(used.begin(), used.end(), 0);
            T tmp = 0;
            while ((tmp = dfs(src, sink, inf))) {
                flow += tmp;
                cost += dist[sink] * tmp;
                fill(used.begin(), used.end(), 0);
            }
            tmp = inf;
            for (int i = 0; i < n; i++) {
                if (!used[i]) continue;
                for (auto& e : g[i]) {
                    if (e.cap > 0 && !used[e.to]) {
                        tmp = min(tmp, (dist[i] + e.cost) - dist[e.to]);
                    }
                }
            }
            if (tmp > inf - n) break;
            for (int i = 0; i < n; i++) {
                if(!used[i]) dist[i] += tmp;
            }
        }
        return {flow, cost};
    }
};

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