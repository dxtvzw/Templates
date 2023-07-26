#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
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

struct SCC {
    vector<int> id;
    vector<vector<int>> groups;
};

struct SCCExec : SCC {
    int n;
    const vector<vector<int>> &g;
    int tm = 0;
    vector<bool> flag;
    vector<int> low, ord, st, gr;
    void dfs(int v) {
        low[v] = ord[v] = tm++;
        st.push_back(v);
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
            gr.clear();
            while (true) {
                int u = st.back();
                st.pop_back();
                gr.push_back(u);
                if (u == v)
                    break;
            }
            for (int x : gr) {
                flag[x] = false;
            }
            groups.push_back(gr);
        }
    }
    SCCExec(const vector<vector<int>> &_g) : n(int(_g.size())), g(_g), flag(n), low(n), ord(n, -1) {
        id = vector<int>(n);
        for (int i = 0; i < n; i++) {
            if (ord[i] == -1)
                dfs(i);
        }
        reverse(groups.begin(), groups.end());
        for (int i = 0; i < int(groups.size()); i++) {
            for (int x : groups[i]) {
                id[x] = i;
            }
        }
    }
};

SCC get_scc(const vector<vector<int>> &g) {
    return SCCExec(g);
}

struct TwoSat {
    vector<bool> res;
    vector<vector<int>> g;
    // (a == a_exp) || (b == b_exp)
    void add_cond(int a, bool a_exp, int b, bool b_exp) {
        g[2 * a + (a_exp ? 0 : 1)].push_back(2 * b + (b_exp ? 1 : 0));
        g[2 * b + (b_exp ? 0 : 1)].push_back(2 * a + (a_exp ? 1 : 0));
    }
    bool exec() {
        int n = int(res.size());
        auto s = get_scc(g);
        for (int i = 0; i < n; i++) {
            if (s.id[2 * i] == s.id[2 * i + 1]) return false;
            res[i] = s.id[2 * i] < s.id[2 * i + 1];
        }
        return true;
    }
    TwoSat() {}
    TwoSat(int n) {
        g = vector<vector<int>>(2 * n);
        res = vector<bool>(n);
    }
};

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
    TwoSat two_sat(n);
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b >> waste;
        two_sat.add_cond(abs(a) - 1, a > 0, abs(b) - 1, b > 0);
    }
    if (two_sat.exec()) {
        cout << "s SATISFIABLE\n";
        cout << "v ";
        for (int i = 0; i < n; i++) {
            cout << (two_sat.res[i] ? i + 1 : -i - 1) << " ";
        }
        cout << "0\n";
    } else {
        cout << "s UNSATISFIABLE\n";
    }

#ifdef LOCAL
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
}