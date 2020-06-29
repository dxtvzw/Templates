#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

vector<multiset<int>> g;
vector<int> ans;

void dfs(int v) {
    while (!g[v].empty()) {
        int to = *g[v].rbegin();
        g[v].erase(g[v].find(to));
        g[to].erase(g[to].find(v));
        dfs(to);
    }
    ans.pb(v);
}

bool Euler_path(int n) {
    int v1 = -1, v2 = -1;
    bool bad = 0;
    for (int i = 1; i <= n; i++) {
        if (g[i].size() & 1) {
            if (v1 == -1) v1 = i;
            else if (v2 == -1) v2 = i;
            else bad = 1;
        }
    }
    if (v1 != -1) {
        g[v1].insert(v2);
        g[v2].insert(v1);
    }
    dfs(1);
    if (v1 != -1) {
        for (int i = 0; i < ans.size() - 1; i++) {
            if (ans[i] == v1 && ans[i + 1] == v2 || ans[i] == v2 && ans[i + 1] == v1) {
                vector<int> ans2;
                for (int j = i + 1; j < ans.size(); j++) {
                    ans2.pb(ans[j]);
                }
                for (int j = 1; j <= i; j++) {
                    ans2.pb(ans[j]);
                }
                ans = ans2;
                break;
            }
        }
    }
    return !bad;
}

/*
const int N = 1e3 + 10;
int g[N][N];
vector<int> ans;

void dfs(int v, int n) {
    for (int to = 1; to <= n; to++) {
        if (g[v][to]) {
            g[v][to]--;
            g[to][v]--;
            dfs(to, n);
        }
    }
    ans.pb(v);
}

bool Euler_path(int n) {
    int v1 = -1, v2 = -1;
    bool bad = 0;
    for (int i = 1; i <= n; i++) {
        int deg = 0;
        for (int j = 1; j <= n; j++) {
            deg += g[i][j];
        }
        if (deg & 1) {
            if (v1 == -1) v1 = i;
            else if (v2 == -1) v2 = i;
            else bad = 1;
        }
    }
    if (v1 != -1) {
        g[v1][v2]++;
        g[v2][v1]++;
    }
    dfs(1, n);
    if (v1 != -1) {
        for (int i = 0; i < ans.size() - 1; i++) {
            if (ans[i] == v1 && ans[i + 1] == v2 || ans[i] == v2 && ans[i + 1] == v1) {
                vector<int> ans2;
                for (int j = i + 1; j < ans.size(); j++) {
                    ans2.pb(ans[j]);
                }
                for (int j = 1; j <= i; j++) {
                    ans2.pb(ans[j]);
                }
                ans = ans2;
                break;
            }
        }
    }
    return !bad;
}
*/

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
