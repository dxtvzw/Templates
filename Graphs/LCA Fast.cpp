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

#define data my_data

const int N = 1e6 + 10;
const int L = 22;
int depth[N], in[N], out[N];
vector<int> g[N];
vector<int> tour;
int data[N], table[N][L];
int lg[N], pw[L];

void dfs_lca(int v = 1, int p = 1) {
    in[v] = tour.size();
    tour.pb(v);
    for (int to : g[v]) {
        if (to != p) {
            depth[to] = depth[v] + 1;
            dfs_lca(to, v);
            tour.pb(v);
        }
    }
    out[v] = tour.size() - 1;
}

void build_sparse_table(int n) {
    pw[0] = 1;
    for (int i = 1; i <= L - 1; i++) {
        pw[i] = pw[i - 1] << 1;
    }
    for (int i = 1, k = 0; i <= N - 1; i <<= 1, k++) {
        for (int j = 0; j <= i - 1 && i + j <= N - 1; j++) {
            lg[i + j] = k;
        }
    }
    for (int i = 1; i <= n; i++) {
        table[i][0] = i;
    }
    for (int k = 1; k <= L - 1; k++) {
        for (int i = 1; i + pw[k] - 1 <= n; i++) {
            if (data[table[i][k - 1]] < data[table[i + pw[k - 1]][k - 1]]) {
                table[i][k] = table[i][k - 1];
            }
            else {
                table[i][k] = table[i + pw[k - 1]][k - 1];
            }
        }
    }
}

int get_pos_min(int l, int r) {
    if (data[table[l][lg[r - l + 1]]] < data[table[r - pw[lg[r - l + 1]] + 1][lg[r - l + 1]]]) {
        return table[l][lg[r - l + 1]];
    }
    else {
        return table[r - pw[lg[r - l + 1]] + 1][lg[r - l + 1]];
    }
}

int lca(int u, int v) {
    if (out[u] > out[v]) {
        swap(u, v);
    }
    return tour[get_pos_min(in[u] + 1, out[v] + 1) - 1];
}

void precalc_lca() {
    dfs_lca();
    for (int i = 1; i <= tour.size(); i++) {
        data[i] = depth[tour[i - 1]];
    }
    build_sparse_table(tour.size());
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    precalc_lca();

#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
