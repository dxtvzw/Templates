#include <bits/stdc++.h>

using namespace std;

// CHECK ALPHABET

const int N = 2e5 + 5;
const int C = 26;
const char min_char = 'a';
int to[N][C];
int link[N];
int sz = 1;
bool is_end[N];

void init() {
    for (int i = 0; i < sz; i++) {
        for (int c = 0; c < C; c++) {
            to[i][c] = 0;
        }
        link[i] = 0;
        is_end[i] = 0;
    }
    sz = 1;
}

void add_str(const string& s) {
    int v = 0;
    for (char c : s) {
        c -= min_char;
        if (!to[v][c]) to[v][c] = sz++;
        v = to[v][c];
    }
    is_end[v] = 1;
}

void push_links() {
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        int u = link[v];
        for (int c = 0; c < C; c++) {
            if (to[v][c]) {
                link[to[v][c]] = v ? to[u][c] : 0;
                q.push(to[v][c]);
            }
            else to[v][c] = to[u][c];
        }
    }
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