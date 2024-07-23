#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
    BETTER WHEN USED MANY TIMES IN ONE RUN (HAS LESS ALLOCATIONS)

    INPUT:
    p cnf 5 6
    1 2 0
    -3 -1 0
    -4 -3 0
    2 -5 0
    5 -2 0
    1 4 0

    OUTPUT:
    s SATISFIABLE
    v -1 2 -3 4 5 0
 */

struct TwoSat {
    static const int N = 2 * 5e5 + 10; // 2 TIMES BIGGER THAN NUMBER OF VARIABLES
    int n, tm = 0, st_sz = 0, group_cnt = 0;
    bool res[N], flag[N];
    vector<int> g[N];
    int id[N], low[N], ord[N], st[N];

    void init(int _n) {
        n = _n;
        for (int i = 0; i < n; i++) {
            res[i] = false;
        }
        for (int i = 0; i < 2 * n; i++) {
            g[i].clear();
            id[i] = 0;
            flag[i] = false;
            low[i] = 0;
            ord[i] = -1;
        }
        tm = 0;
        st_sz = 0;
        group_cnt = 0;
    }
    void dfs(int v) {
        low[v] = ord[v] = tm++;
        st[st_sz++] = v;
        flag[v] = true;
        for (int to : g[v]) {
            if (ord[to] == -1) {
                dfs(to);
                low[v] = min(low[v], low[to]);
            } else if (flag[to]) {
                low[v] = min(low[v], ord[to]);
            }
        }
        if (low[v] == ord[v]) {
            group_cnt++;
            while (true) {
                int u = st[--st_sz];
                id[u] = group_cnt;
                flag[u] = false;
                if (u == v)
                    break;
            }
        }
    }
    void get_scc() {
        for (int i = 0; i < 2 * n; i++) {
            if (ord[i] == -1)
                dfs(i);
        }
        for (int i = 0; i < 2 * n; i++) {
            id[i] = group_cnt - id[i];
        }
    }

    // (a == a_exp) || (b == b_exp)
    void add_cond(int a, bool a_exp, int b, bool b_exp) {
        g[2 * a + (a_exp ? 0 : 1)].push_back(2 * b + (b_exp ? 1 : 0));
        g[2 * b + (b_exp ? 0 : 1)].push_back(2 * a + (a_exp ? 1 : 0));
    }
    bool exec() {
        get_scc();
        for (int i = 0; i < n; i++) {
            if (id[2 * i] == id[2 * i + 1]) return false;
            res[i] = id[2 * i] < id[2 * i + 1];
        }
        return true;
    }
};

TwoSat ts;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    string waste;
    cin >> waste >> waste;
    int n, m;
    cin >> n >> m;
    ts.init(n);
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b >> waste;
        ts.add_cond(abs(a) - 1, a > 0, abs(b) - 1, b > 0);
    }
    if (ts.exec()) {
        cout << "s SATISFIABLE\n";
        cout << "v ";
        for (int i = 0; i < n; i++) {
            cout << (ts.res[i] ? i + 1 : -i - 1) << " ";
        }
        cout << "0\n";
    } else {
        cout << "s UNSATISFIABLE\n";
    }

#ifdef LOCAL
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
}