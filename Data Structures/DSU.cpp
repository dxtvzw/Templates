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
    int Parent[N], Rank[N], cnt;
    void init(const int& n) {
        for (int i = 1; i <= n; i++) {
            Parent[i] = i, Rank[i] = 0;
        }
        cnt = n;
    }
    int find(const int& v) {
        if (Parent[v] == v) return v;
        else return Parent[v] = find(Parent[v]);
    }
    void unite(const int& u, const int& v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        if (Rank[U] < Rank[V]) swap(U, V);
        if (Rank[V] == Rank[U]) Rank[U]++;
        Parent[V] = U, cnt--;
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
