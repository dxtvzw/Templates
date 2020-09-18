#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

//O(n^3)

const int N = 205;
vector<int> g[N];
int match[N], parent[N], base[N];
bool used[N], blossom[N];
bool used_lca[N];
queue<int> q;

int lca(int a, int b) {
    for (int i = 0; i <= N - 1; i++) {
        used_lca[i] = 0;
    }
    while (1) {
        a = base[a];
        used_lca[a] = 1;
        if (!match[a]) break;
        a = parent[match[a]];
    }
    while (1) {
        b = base[b];
        if (used_lca[b]) return b;
        b = parent[match[b]];
    }
}

void mark_path(int v, int b, int child) {
    while (base[v] != b) {
        blossom[base[v]] = blossom[base[match[v]]] = 1;
        parent[v] = child;
        child = match[v];
        v = parent[match[v]];
    }
}

int find_path(int root, int n) {
    for (int i = 1; i <= n; i++) {
        used[i] = parent[i] = 0;
        base[i] = i;
    }
    used[root] = 1;
    while (!q.empty()) q.pop();
    q.push(root);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
        if (base[v] == base[to] || match[v] == to)  continue;
            if (to == root || match[to] && parent[match[to]]) {
            int cur_base = lca (v, to);
                for (int i=1; i<=n; i++) blossom[i] = 0;
                mark_path(v, cur_base, to);
                mark_path(to, cur_base, v);
                for (int i=1; i<=n; i++) {
                    if (blossom[base[i]]) {
                        base[i] = cur_base;
                        if (!used[i]) {
                            used[i] = 1;
                            q.push(i);
                        }
                    }
                }
            }
            else if (!parent[to]) {
                parent[to] = v;
                if (!match[to]) return to;
                to = match[to];
                used[to] = 1;
                q.push(to);
            }
        }
    }
    return 0;
}

void Edmonds(int n) {
    for (int i = 1; i <= n; i++) {
        if (!match[i]) {
            int v = find_path(i, n);
            while (v) {
                int match_par_v = match[parent[v]];
                match[v] = parent[v];
                match[parent[v]] = v;
                v = match_par_v;
            }
        }
    }
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
