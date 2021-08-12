#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

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
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif



#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
