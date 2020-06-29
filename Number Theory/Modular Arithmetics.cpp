#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

#define div divi

const int mod = 1e9 + 7;

inline int add(int a, int b) {
    if (a + b >= mod) return a + b - mod;
    else return a + b;
}

inline int sub(int a, int b) {
    if (a - b < 0) return a - b + mod;
    else return a - b;
}

inline int mult(int a, int b) {
    return 1ll * a * b % mod;
}

inline int binpow(int a, int n) {
    int res = 1;
    while (n) {
        if (n & 1) {
            res = mult(res, a);
        }
        a = mult(a, a);
        n >>= 1;
    }
    return res;
}

inline int inv(int a) {
    return binpow(a, mod - 2);
}

inline int div(int a, int b) {
    return mult(a, inv(b));
}

const int N = 2e5 + 10;
int f[N];
int f_inv[N];

inline int C(int n, int k) {
    if (n < k) return 0;
    return mult(f[n], mult(f_inv[k], f_inv[n-k]));
}

void init() {
    f[0] = 1;
    for (int i = 1; i <= N - 1; i++) {
        f[i] = mult(f[i - 1], i);
    }
    f_inv[N - 1] = inv(f[N - 1]);
    for (int i = N - 2; i >= 0; i--) {
        f_inv[i] = mult(f_inv[i + 1], i + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    init();

#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
