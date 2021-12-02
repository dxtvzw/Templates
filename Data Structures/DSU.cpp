#include <bits/stdc++.h>

using namespace std;

struct DSU {
    static const int N = 1e6 + 10;
    int Parent[N], Rank[N], Size[N], cnt;
    void init(int n) {
        for (int i = 1; i <= n; i++) {
            Parent[i] = i, Rank[i] = 0, Size[i] = 1;
        }
        cnt = n;
    }
    int find(int v) {
        if (Parent[v] == v) return v;
        else return Parent[v] = find(Parent[v]);
    }
    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (Rank[u] < Rank[v]) swap(u, v);
        if (Rank[v] == Rank[u]) Rank[u]++;
        Parent[v] = u, cnt--;
        Size[u] += Size[v];
    }
};

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