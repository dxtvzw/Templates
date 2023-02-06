#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

mt19937 rnd;

struct Kuhn {
    static const int N = 2e5 + 10;
    vector<int> g[N];
    int used[N] = {};
    bool used1[N] = {};
    int match[N] = {};
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    bool dfs(int v, int root) {
        if (used[v] == root) return false;
        used[v] = root;
        for (int to : g[v]) {
            if (!match[to] || dfs(match[to], root)) {
                match[to] = v;
                match[v] = to;
                used1[to] = true;
                used1[v] = true;
                return true;
            }
        }
        return false;
    }
    int maxmatching(int n) {
        for (int i = 1; i <= n; i++) {
            match[i] = 0;
            used1[i] = false;
            used[i] = 0;
        }
        for (int i = 1; i <= n; i++) {
            if (used1[i]) continue;
            // shuffle(g[i].begin(), g[i].end(), rnd);
            for (int to : g[i]) {
                if (!match[to]) {
                    match[i] = to;
                    match[to] = i;
                    used1[i] = true;
                    used1[to] = true;
                    break;
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            if (used1[i]) continue;
            dfs(i, i);
        }
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (match[i]) {
                cnt++;
            }
        }
        return cnt / 2;
    }
};

Kuhn kn;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif



#ifdef LOCAL
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
}
