#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct HopcroftKarp {
    static const int N = 1e5 + 10;
    vector<int> adj_left[N];
    int matchL[N] = {};
    int matchR[N] = {};
    int root[N], prev[N], qq[N];

    void add_edge(int u, int v) {
        adj_left[u].push_back(v);
    }
    void init(int L, int R) {
        for (int i = 1; i <= L; i++) {
            adj_left[i].clear();
            matchL[i] = 0;
        }
        for (int i = 1; i <= R; i++) {
            matchR[i] = 0;
        }
    }
    void init_matching(int L, int R) {
        for (int i = 1; i <= L; i++) {
            matchL[i] = 0;
        }
        for (int i = 1; i <= R; i++) {
            matchR[i] = 0;
        }
    }
    int maxmatching(int L, int R) {
        int sz = 0;
        for (bool updated = true; updated; ) {
            updated = false;
            for (int i = 1; i <= L; i++) {
                root[i] = -1;
                prev[i] = -1;
                qq[i] = 0;
            }
            int qi = 0, qj = 0;
            for (int i = 1; i <= L; i++) {
                if (matchL[i] == 0) {
                    qq[qj++] = i, root[i] = i, prev[i] = i;
                }
            }
            while (qi < qj) {
                int u = qq[qi++];
                if (matchL[root[u]] != 0) {
                    continue;
                }
                for (int v : adj_left[u]) {
                    if (matchR[v] == 0) {
                        while (v != 0) {
                            matchR[v] = u, swap(matchL[u], v), u = prev[u];
                        }
                        updated = true;
                        sz++;
                        break;
                    }
                    if (prev[matchR[v]] == -1) {
                        v = matchR[v], prev[v] = u, root[v] = root[u], qq[qj++] = v;
                    }
                }
            }
        }
        return sz;
    }
};

HopcroftKarp hk;

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