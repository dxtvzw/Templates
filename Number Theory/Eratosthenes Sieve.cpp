#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

const int N = 1e6 + 10;
bool prime[N];

void find_primes() {
    for (int i = 0; i <= N - 1; i++) {
        prime[i] = 1;
    }
    prime[0] = prime[1] = 0;
    for (int i = 2; i <= N - 1; i++) {
        if (prime[i]) {
            if (i * 1ll * i <= N - 1) {
                for (int j = i * i; j <= N - 1; j += i) {
                    prime[j] = 0;
                }
            }
        }
    }
}

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
