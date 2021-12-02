#include <bits/stdc++.h>

using namespace std;

vector<multiset<int>> g;
vector<int> ans;

void dfs(int v) {
    while (!g[v].empty()) {
        int to = *g[v].rbegin();
        g[v].erase(g[v].find(to));
        g[to].erase(g[to].find(v));
        dfs(to);
    }
    ans.push_back(v);
}

bool Euler_path(int n) {
    int v1 = -1, v2 = -1;
    bool bad = false;
    for (int i = 1; i <= n; i++) {
        if (g[i].size() & 1) {
            if (v1 == -1) v1 = i;
            else if (v2 == -1) v2 = i;
            else bad = true;
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
                    ans2.push_back(ans[j]);
                }
                for (int j = 1; j <= i; j++) {
                    ans2.push_back(ans[j]);
                }
                ans = ans2;
                break;
            }
        }
    }
    return !bad;
}

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