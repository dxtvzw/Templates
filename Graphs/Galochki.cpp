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

// tested on https://codeforces.com/contest/1519/problem/E

const int N = 1e6 + 10;
vector<pii> ans;
vector<pii> g[N];
int depth[N], mem[N];
bool used[N], in_tree[N], dead[N];

void add_edge(int u, int v, int id) {
    g[u].pb({v, id});
    g[v].pb({u, id});
}

void add(int i, int j) {
    ans.pb({i, j});
    dead[i] = dead[j] = 1;
}

void dfs(int v) {
    used[v] = 1;
    for (auto [to, id] : g[v]) {
        if (!used[to]) {
            in_tree[id] = 1;
            depth[to] = depth[v] + 1;
            dfs(to);
        }
    }
    vector<int> children;
    for (auto [to, id] : g[v]) {
        if (in_tree[id] && !dead[id] && depth[to] == depth[v] + 1) {
            if (mem[to] && !dead[mem[to]]) {
                add(id, mem[to]);
            }
            else {
                children.pb(id);
            }
        }
    }
    for (int i = 0; i + 1 < children.size(); i += 2) {
        add(children[i], children[i + 1]);
    }
    vector<int> extra;
    for (auto [to, id] : g[v]) {
        if (!in_tree[id] && !dead[id]) {
            extra.pb(id);
        }
    }
    for (int i = 0; i + 1 < extra.size(); i += 2) {
        add(extra[i], extra[i + 1]);
    }
    if ((children.size() & 1) && (extra.size() & 1)) {
        add(children.back(), extra.back());
    }
    else if (children.size() & 1) {
        mem[v] = children.back();
    }
    else if (extra.size() & 1) {
        mem[v] = extra.back();
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
