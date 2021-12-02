#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int L = 20;
const int N = L + L + 10;
ll g[N]; // 1 - no edge, 0 - is edge
int dp[2][(1 << L) + 10]; // size of maximal independent set on a subgraph on mask
int mem[2][(1 << L) + 10]; // mask of maximal independent set

bool getBit(ll mask, int bit) {
    return (mask >> bit) & 1;
}

ll setBit(ll mask, int bit) {
    return mask | (1ll << bit);
}

ll unsetBit(ll mask, int bit) {
    return mask & (~(1ll << bit));
}

void calc_dp(int l, int r, bool t) {
    dp[t][0] = 0;
    mem[t][0] = 0;
    for (int mask = 1; mask < (1 << (r - l + 1)); mask++) {
        dp[t][mask] = 0;
        mem[t][mask] = 0;
        bitset<N> cur(mask);
        int v = cur._Find_first() + l;
        cur[v - l] = 0;
        int p = cur.to_ulong();
        int q = p & (g[v] >> l);
        if (dp[t][p] < 1 + dp[t][q]) {
            dp[t][mask] = 1 + dp[t][q];
            mem[t][mask] = setBit(mem[t][q], v - l);
        }
        else {
            dp[t][mask] = dp[t][p];
            mem[t][mask] = mem[t][p];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL_ALIKHAN
    freopen("input.txt", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        g[i] = (1ll << (n + 1)) - 1;
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        u++, v++; // delete this if vertices are initially numbered from 1
        g[u] = unsetBit(g[u], v);
        g[v] = unsetBit(g[v], u);
    }
    int a = 1, b = n / 2, c = n / 2 + 1, d = n;
    calc_dp(a, b, 0);
    calc_dp(c, d, 1);
    int ans = 0;
    int mask_lef = 0, mask_rig = 0;
    for (int lef = 0; lef < (1 << (b - a + 1)); lef++) {
        if (mem[0][lef] != lef) {
            continue;
        }
        ll rig = (1 << (d - c + 1)) - 1;
        rig <<= c;
        for (int i = a; i <= b; i++) {
            if (getBit(lef, i - a)) {
                rig &= g[i];
            }
        }
        rig = mem[1][rig >> c];
        if (ans < dp[0][lef] + dp[1][rig]) {
            ans = dp[0][lef] + dp[1][rig];
            mask_lef = lef;
            mask_rig = rig;
        }
    }
    cout << ans << "\n";
    ll res = 0;
    for (int i = a; i <= b; i++) {
        if (getBit(mask_lef, i - a)) {
            cout << i - 1 << " ";
            res = setBit(res, i);
        }
    }
    for (int i = c; i <= d; i++) {
        if (getBit(mask_rig, i - c)) {
            cout << i - 1 << " ";
            res = setBit(res, i);
        }
    }
    cout << "\n";

#ifdef LOCAL_ALIKHAN
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}