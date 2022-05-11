#include <bits/stdc++.h>

using namespace std;

const int C = 1e6 + 10;
bool prime[C];
int prime_div[C];
vector<pair<int, int>> pf[C];

void find_primes() {
    for (int i = 0; i <= C - 1; i++) {
        prime[i] = true;
        prime_div[i] = i;
    }
    prime[0] = prime[1] = false;
    for (int i = 2; i <= C - 1; i++) {
        if (prime[i]) {
            if (i * 1ll * i <= C - 1) {
                for (int j = i * i; j <= C - 1; j += i) {
                    prime[j] = false;
                    prime_div[j] = i;
                }
            }
        }
    }
    for (int i = 2; i <= C - 1; i++) {
        if (prime[i]) {
            pf[i] = {{i, 1}};
        } else {
            pf[i] = pf[i / prime_div[i]];
            bool ok = true;
            for (int j = 0; j < pf[i].size(); j++) {
                if (pf[i][j].first == prime_div[i]) {
                    ok = false;
                    pf[i][j].second++;
                }
            }
            if (ok) {
                pf[i].emplace_back(prime_div[i], 1);
                for (int j = int(pf[i].size()) - 1; j >= 1; j--) {
                    if (pf[i][j - 1].first > pf[i][j].first) {
                        swap(pf[i][j - 1], pf[i][j]);
                    }
                }
            }
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