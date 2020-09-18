#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//typedef __int128_t LL;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

template<int mod>
struct Modular {
    int val;
    Modular(int new_val = 0) {
        val = new_val;
    }
    Modular operator+(const Modular& ot) const {
        if (val + ot.val >= mod) return val + ot.val - mod;
        else return val + ot.val;
    }
    Modular operator-(const Modular& ot) const {
        if (val - ot.val < 0) return val - ot.val + mod;
        else return val - ot.val;
    }
    Modular operator*(const Modular& ot) const {
        return 1ll * val * ot.val % mod;
    }
    friend Modular binpow(Modular a, ll n) {
        Modular res = 1;
        for (; n; n >>= 1) {
            if (n & 1) res *= a;
            a *= a;
        }
        return res;
    }
    friend Modular inv(const Modular& a) {
        return binpow(a, mod - 2);
    }
    Modular operator/(const Modular& ot) const {
        return 1ll * val * inv(ot).val % mod;
    }
    Modular& operator++() {
        if (val + 1 == mod) return 0;
        else return val + 1;
    }
    void operator+=(const Modular& ot) {
        val += ot.val;
        if (val >= mod) {
            val -= mod;
        }
    }
    void operator-=(const Modular& ot) {
        val -= ot.val;
        if (val < 0) {
            val += mod;
        }
    }
    void operator*=(const Modular& ot) {
        val = 1ll * val * ot.val % mod;
    }
    void operator/=(const Modular& ot) {
        val = 1ll * val * inv(ot).val % mod;
    }
    bool operator==(const Modular& ot) const {
        return val == ot.val;
    }
    bool operator!=(const Modular& ot) const {
        return val != ot.val;
    }
};

template<int mod>
istream& operator>>(istream& istr, Modular<mod>& x) {
    return istr >> x.val;
}

template<int mod>
ostream& operator<<(ostream& ostr, const Modular<mod>& x) {
    return ostr << x.val;
}

const int mod = 1000000007;
using Mint = Modular<mod>;

const int N = 2e5 + 10;
Mint fact[N], inv_fact[N];

void init() {
    fact[0] = 1;
    for (int i = 1; i <= N - 1; i++) {
        fact[i] = fact[i - 1] * i;
    }
    inv_fact[N - 1] = inv(fact[N - 1]);
    for (int i = N - 2; i >= 0; i--) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1);
    }
}

Mint C(int n, int k) {
    if (n < 0 || k < 0) return 0;
    return n >= k ? fact[n] * inv_fact[k] * inv_fact[n - k] : 0;
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
