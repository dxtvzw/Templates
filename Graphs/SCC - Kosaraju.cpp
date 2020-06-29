#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

const int N = 2e5 + 10;
vector<int> g[2][N];
bool used[N];
vector<int> post;
vector<vector<int>> comps;

void add_edge(int u, int v) {
    g[0][u].pb(v);
    g[1][v].pb(u);
}

void dfs_inv(int v) {
    used[v] = 1;
    for (int to : g[1][v]) {
        if (!used[to]) {
            dfs_inv(to);
        }
    }
    post.pb(v);
}

void dfs(int v, vector<int>& comp) {
    used[v] = 1;
    comp.pb(v);
    for (int to : g[0][v]) {
        if (!used[to]) {
            dfs(to, comp);
        }
    }
}

void Kosaraju(int n) {
	for (int i = 1; i <= n; i++) {
        used[i] = 0;
	}
	for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs_inv(i);
        }
	}
	reverse(post.begin(), post.end());
	for (int i = 1; i <= n; i++) {
        used[i] = 0;
	}
	for (int v : post) {
		if (!used[v]) {
			vector<int> comp;
			dfs(v, comp);
			comps.pb(comp);
		}
	}
	// comps = reversed topsort
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
