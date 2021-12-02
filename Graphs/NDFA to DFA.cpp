#include <bits/stdc++.h>

using namespace std;

// test on problem: https://official.contest.yandex.com/ptz-summer-2021/contest/28728/problems/I5/?success=52478567#7/2021_05_22/uLnusSUiEb

// transforms NDFA of size n to DFA of size 2^n
// NDFA is based on the alphabet {0, 1}
// initial vertex is 0
// mark[i] = 1 iff i is a terminal vertex in NDFA
// flag[mask] = 1 iff mask is a terminal vertex in DFA
// flag[mask] = 1 iff mask contains a terminal vertex in NDFA

const int inf = 1e9 + 10;
const int K = 20;
const int N = K + 10;
const int M = (1 << K) + 10;
bool g[2][N][N], mark[N];
int tmp[2][N];
int ptr[2][M], flag[M];
int dist[M];

void add_edge(int u, int v) {
    g[0][u][v] = g[1][u][v] = true;
}

void init() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            g[0][i][j] = g[1][i][j] = false;
        }
        mark[i] = false;
    }
}

bool getBit(int mask, int bit) {
    return mask & (1 << bit);
}

int setBit(int mask, int bit) {
    return mask | (1 << bit);
}

int unsetBit(int mask, int bit) {
    return mask & (~(1 << bit));
}

void print_mask(int mask, int n) {
    for (int i = 0; i < n; i++) {
        cout << getBit(mask, i);
    }
    cout << "\n";
}

void transform_ndfa_to_dfa(int n) {
    for (int i = 0; i < n; i++) {
        tmp[0][i] = 0;
        tmp[1][i] = 0;
    }
    for (int i = 0; i < (1 << n); i++) {
        ptr[0][i] = ptr[1][i] = 0;
        flag[i] = 0;
        dist[i] = inf;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int t = 0; t < 2; t++) {
                if (g[t][i][j]) {
                    tmp[t][i] = setBit(tmp[t][i], j);
                }
            }
        }
    }
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (getBit(mask, i)) {
                ptr[0][mask] |= tmp[0][i];
                ptr[1][mask] |= tmp[1][i];
                flag[mask] |= mark[i];
            }
        }
    }
}

// calculates minimal k, such that there exists an unreadable string of length k
// if every string is readable, then k = -1
int calc(int n) {
    transform_ndfa_to_dfa(n);
    queue<int> q;
    q.push(1);
    dist[1] = 0;
    if (!flag[1]) {
        return 0;
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (!flag[ptr[0][v]]) {
            return dist[v] + 1;
        }
        else if (dist[ptr[0][v]] > dist[v] + 1) {
            dist[ptr[0][v]] = dist[v] + 1;
            q.push(ptr[0][v]);
        }
        if (!flag[ptr[1][v]]) {
            return dist[v] + 1;
        }
        else if (dist[ptr[1][v]] > dist[v] + 1) {
            dist[ptr[1][v]] = dist[v] + 1;
            q.push(ptr[1][v]);
        }
    }
    return -1;
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