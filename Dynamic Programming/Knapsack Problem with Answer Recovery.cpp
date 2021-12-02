#include <bits/stdc++.h>

using namespace std;

const int N = 7e4 + 10;
int a[N];
// after iterating i'th prefix, dp[j] = 1 iff we can get sum j on prefix i
bitset<N> dp, new_dp, temp;
// mem[j] = first prefix at which we can achieve sum j
int mem[N];
bool used[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL_ALIKHAN
    freopen("input.txt", "r", stdin);
#endif

    int n, s;
    cin >> n >> s;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        new_dp = dp | (dp << a[i]);
        temp = dp;
        dp = new_dp;
        new_dp ^= temp;
        while (new_dp != 0) {
            int bit = new_dp._Find_first();
            mem[bit] = i;
            new_dp[bit] = 0;
        }
    }
    if (!dp[s]) {
        cout << "-1\n";
        return 0;
    }
    for (int ptr = mem[s]; s > 0; ptr = mem[s]) {
        used[ptr] = 1;
        s -= a[ptr];
    }

#ifdef LOCAL_ALIKHAN
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}