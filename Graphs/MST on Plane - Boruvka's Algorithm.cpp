#include <bits/stdc++.h>

using namespace std;

struct DSU {
    static const int N = 5e3 + 10;
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
} dsu;

struct Point {
    double x, y;
};

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

const int N = 5e3 + 10;
Point a[N];
pair<int, int> best[N];
double ans;

void unite(const int& u, const int& v) {
    ans += dist(a[u], a[v]) * (dsu.find(u) != dsu.find(v));
    dsu.unite(u, v);
}

double Boruvka(int n) {
    dsu.init(n);
    while (dsu.cnt > 1) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dsu.find(i) == dsu.find(j)) continue;
                int I = dsu.find(i);
                if (!best[I].first || dist(a[best[I].first], a[best[I].second]) > dist(a[i], a[j])) {
                    best[I] = {i, j};
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            if (best[i].first) {
                unite(best[i].first, best[i].second);
                best[i] = {0, 0};
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL_ALIKHAN
    freopen("input.txt", "r", stdin);
#endif

    cout << fixed << setprecision(6);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    cout << Boruvka(n) << "\n";

#ifdef LOCAL_ALIKHAN
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}