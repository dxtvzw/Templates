#include <bits/stdc++.h>

using namespace std;

const int C = 1e6 + 10;
bool prime[C];
int prime_div[C];

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