#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

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
        vec.pb(t);
        t = par[t];
    }
    vec.pb(s);
    reverse(vec.begin(), vec.end());
    for (int i = 1; i <= n; i++) {
        pos[i] = -1;
    }
    for (int i = 0; i < vec.size(); i++) {
        pos[vec[i]] = i;
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
