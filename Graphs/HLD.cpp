#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;
/*
    RANGE UPDATES

struct segment_tree {
    int N;
    vector<int> t;
    segment_tree(int n) {
        N = n;
        t.resize(2 * N + 5, 0);
    }
    void clear() {
        for (int& i : t) {
            i = 0;
        }
    }
    void update(int l, int r, int val) {
        for (l += N, r += N; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) t[l++] += val;
            if (!(r & 1)) t[r--] += val;
        }
    }
    int get(int pos) {
        ll res = 0;
        for (pos += N; pos > 0; pos >>= 1) {
            res += t[pos];
        }
        return res;
    }
};
*/

struct segment_tree {
    int N;
    vector<int> t;
    segment_tree(int n) {
        N = n;
        t.resize(2 * N + 5);
    }
    void update(int pos, int val) {
        for (t[pos += N] += val; pos > 1; pos >>= 1) {
            t[pos >> 1] = t[pos] + t[pos ^ 1];
        }
    }
    int get(int l, int r) {
        int res = 0;
        for (l += N, r += N; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (!(r & 1)) res += t[r--];
        }
        return res;
    }
};

struct heavy_path {
    vector<int> path;
    segment_tree t;
};

const int N = 1e5 + 10;
const int L = 17;
vector<int> g[N];
int in[N], out[N];
int up[N][L];
int timer;
int depth[N];

void dfs_lca(int v = 1, int p = 1) {
	in[v] = ++timer;
	up[v][0] = p;
	for (int i = 1; i < L; i++) {
		up[v][i] = up[up[v][i-1]][i-1];
	}
	for (int to : g[v]) {
		if (to != p) {
            depth[to] = depth[v] + 1;
            dfs_lca(to, v);
		}
	}
	out[v] = ++timer;
}

bool is_anc(int u, int v) {
	return in[u] <= in[v] && in[v] <= out[u];
}

int lca(int u, int v) {
	if (is_anc(u, v)) return u;
	else if (is_anc(v, u)) return v;
	for (int i = L - 1; i >= 0; i--) {
		if (!is_anc(up[u][i], v)) u = up[u][i];
	}
	return up[u][0];
}

int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

int sz[N];
vector<int> start;
vector<heavy_path> hld;
int id[N], pos[N];

bool heavy(int v, int to) {
    return sz[to] >= (sz[v] + 1) / 2;
}

void dfs_hld(int v = 1, int p = 1) {
    sz[v] = 1;
    for (int to : g[v]) {
        if (to != p) {
            dfs_hld(to, v);
            sz[v] += sz[to];
        }
    }
    bool light = 1;
    for (int to : g[v]) {
        if (to != p && heavy(v, to)) {
            light = 0;
            break;
        }
    }
    if (light) start.pb(v);
}

void heavy_light_decomposition(int root = 1) {
    dfs_lca(root, root);
    dfs_hld(root, root);
    for (int i : start) {
        int v = i;
        vector<int> path = {v};
        while (v != root && heavy(up[v][0], v)) {
            v = up[v][0];
            path.pb(v);
        }
        reverse(path.begin(), path.end());
        segment_tree t(path.size());
        hld.pb({path, t});
    }
    for (int i = 0; i < hld.size(); i++) {
        for (int j = 0; j < hld[i].path.size(); j++) {
            id[hld[i].path[j]] = i;
            pos[hld[i].path[j]] = j;
        }
    }
}

/*
    RANGE UPDATES

void update(int u, int v, int val) {
    while (id[v] != id[u]) {
        hld[id[v]].t.update(0, pos[v], val);
        v = par[hld[id[v]].path[0]];
    }
    hld[id[v]].t.update(pos[u] + 1, pos[v], val);
}

int get(int v) {
    return hld[id[v]].t.get(pos[v]);
}
*/

void update(int v, int val) {
    hld[id[v]].t.update(pos[v], val);
}

int get(int u, int v) {
    if (is_anc(u, v)) {
        int res = 0;
        while (id[v] != id[u]) {
            res = max(res, hld[id[v]].t.get(0, pos[v]));
            v = up[hld[id[v]].path[0]][0];
        }
        res = max(res, hld[id[v]].t.get(pos[u], pos[v]));
        return res;
    }
    else if (is_anc(v, u)) {
        return get(v, u);
    }
    else {
        int l = lca(u, v);
        return max(get(l, u), get(l, v));
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    heavy_light_decomposition();

#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
