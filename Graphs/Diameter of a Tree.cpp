#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
vector<int> g[N];
int depth[N];
vector<int> vec;
int pos[N];
int par[N];

void dfs(int v, int p = 0) {
    par[v] = p;
    for (int to : g[v]) {
        if (to != p) {
            depth[to] = depth[v] + 1;
            dfs(to, v);
        }
    }
}

void find_diameter(int n) {
    dfs(1);
    depth[0] = -1;
    int s = 0, t = 0;
    for (int i = 1; i <= n; i++) {
        if (depth[i] > depth[s]) {
            s = i;
        }
    }
    depth[s] = 0;
    dfs(s);
    for (int i = 1; i <= n; i++) {
        if (depth[i] > depth[t]) {
            t = i;
        }
    }
    while (t != s) {
        vec.push_back(t);
        t = par[t];
    }
    vec.push_back(s);
    reverse(vec.begin(), vec.end());
    for (int i = 1; i <= n; i++) {
        pos[i] = -1;
    }
    for (int i = 0; i < vec.size(); i++) {
        pos[vec[i]] = i;
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