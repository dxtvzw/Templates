#include <bits/stdc++.h>

using namespace std;

// tested on https://codeforces.com/contest/1519/problem/E

const int N = 1e6 + 10;
vector<pair<int, int>> ans;
vector<pair<int, int>> g[N];
int depth[N], mem[N];
bool used[N], in_tree[N], dead[N];

void add_edge(int u, int v, int id) {
    g[u].emplace_back(v, id);
    g[v].emplace_back(u, id);
}

void add(int i, int j) {
    ans.emplace_back(i, j);
    dead[i] = dead[j] = true;
}

void dfs(int v) {
    used[v] = true;
    for (auto [to, id] : g[v]) {
        if (!used[to]) {
            in_tree[id] = true;
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
                children.push_back(id);
            }
        }
    }
    for (int i = 0; i + 1 < children.size(); i += 2) {
        add(children[i], children[i + 1]);
    }
    vector<int> extra;
    for (auto [to, id] : g[v]) {
        if (!in_tree[id] && !dead[id]) {
            extra.push_back(id);
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