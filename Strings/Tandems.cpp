#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128_t LL;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

const int N = 5e5 + 10;
vector<pii> ans[N];
int s[N], p[N];
int z[N], z1[N], z2[N];
ll sc[N], sc1[N], sc2[N];

void calcZ(int n) {
    for (int i = 0; i < n; i++) {
        z[i] = 0;
    }
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while(i + z[i] < n && p[z[i]] == p[i + z[i]]) z[i]++;
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
}

void solve(int l, int r) {
    if (l + 1 >= r) return;
    int m = (l + r) / 2;
    solve(l, m);
    int len = 0;
    for (int i = m; i < r; i++) {
        p[len++] = s[i];
    }
    for (int i = l; i < m; i++) {
        p[len++] = s[i];
    }
    calcZ(len);
    for (int i = 0; i < len; i++) {
        z1[i] = z[i];
    }
    len = 0;
    for (int i = m - 1; i >= l; i--) {
        p[len++] = s[i];
    }
    for (int i = r - 1; i >= m; i--) {
        p[len++] = s[i];
    }
    calcZ(len);
    for (int i = 0; i < len; i++) {
        z2[i] = z[i];
    }
    for (int k = 1; 2 * k <= len; k++) {
        if (z1[len - k] > 0) {
            int L = max(l, m - k - z2[k]);
            int R = min(m, m - 2 * k + z1[len - k] + 1);
            if (L < R) ans[k].pb({L, R});
        }
        if (z1[len - k] == k) {
            ans[k].pb({m - k, m - k + 1});
        }
        if (z2[len - k] > 0) {
            int L = max(m - k + 1, m - z2[len - k]);
            int R = min(r - 2 * k + 1, m - k + z1[k] + 1);
            if (L < R) ans[k].pb({L, R});
        }
    }
    solve(m, r);
}

void update(int len, int lef, int rig) {
    if (lef == rig) return;
    int L = 2, R = (rig - lef) / len + 2;
    if (L <= R) {
        sc1[L] += rig - lef;
        sc1[R + 1] -= rig - lef;
        sc2[L] += len;
        sc2[R + 1] -= len;
    }
}

void build(int n) {
    for (int i = 1; i <= n; i++) {
        sc1[i] += sc1[i - 1];
        sc2[i] += sc2[i - 1];
        sc[i] = sc1[i] - (i - 2) * sc2[i];
    }
}

void find_number_of_tandems(int n) {
    solve(0, n);
    for (int len = 1; len <= n; len++) {
        pii cur = {0, 0};
        ans[len].erase(unique(ans[len].begin(), ans[len].end()), ans[len].end());
        for (pii z : ans[len]) {
            if (cur.S < z.F) {
                update(len, cur.F, cur.S);
                cur = z;
            } else {
                cur.S = z.S;
            }
        }
        update(len, cur.F, cur.S);
    }
    build(n);
    // sc[i] = # of k-tandems (string repeats k times)
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    find_number_of_tandems(n);
    for (int i = 2; i <= n; i++) {
        cout << sc[i] << " ";
    }
    cout << "\n";

#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
