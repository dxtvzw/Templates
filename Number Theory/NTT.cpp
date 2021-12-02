#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef __int128_t LL;

typedef vector<ll> poly;

ostream &operator<<(ostream &ostr, const poly &x) {
    for (ll it: x) ostr << it << " ";
    return ostr;
}

const int B = 3;
const ll P[4] = {998244353, 1045430273, 1053818881, 1051721729};
const ll G[4] = {565042129, 36657000, 973782742, 531741956};

struct NTT {
    static const int K = 1 << 20;
    ll precalc_w[K / 2];
    ll w[K];
    ll p, g;

    ll binpow(ll a, ll b) {
        ll res = 1;
        while (b) {
            if (b & 1) res = res * a % p;
            b >>= 1;
            a = a * a % p;
        }
        return res;
    }

    void init(ll _p, ll _g) {
        p = _p, g = _g;
        precalc_w[0] = 1;
        for (int i = 1; i < K / 2; i++) {
            precalc_w[i] = precalc_w[i - 1] * g % p;
        }
        for (int i = 1; i < K; i *= 2) {
            for (int j = 0; j < i; j++) {
                w[i + j] = precalc_w[K / (2 * i) * j];
            }
        }
    }

    void fft(ll *in, ll *out, int n, int k = 1) {
        if (n == 1) {
            *out = *in;
            return;
        }
        n /= 2;
        fft(in, out, n, 2 * k);
        fft(in + k, out + n, n, 2 * k);
        for (int i = 0; i < n; i++) {
            ll t = out[i + n] * w[i + n] % p;
            out[i + n] = out[i] - t;
            if (out[i + n] < 0) out[i + n] += p;
            out[i] += t;
            if (out[i] >= p) out[i] -= p;
        }
    }

    static void align(poly &a, poly &b) {
        int n = a.size() + b.size() - 1;
        while (a.size() < n) a.push_back(0);
        while (b.size() < n) b.push_back(0);
    }

    poly eval(poly a) {
        while (__builtin_popcount(a.size()) != 1) a.push_back(0);
        poly res(a.size());
        fft(a.data(), res.data(), a.size());
        return res;
    }

    poly inter(poly a) {
        int n = a.size();
        poly inv(n);
        fft(a.data(), inv.data(), n);
        poly res(n);
        for (int i = 0; i < n; i++) {
            res[i] = inv[i] * binpow(n, p - 2) % p;
        }
        reverse(res.begin() + 1, res.end());
        return res;
    }

    poly mult(poly a, poly b) {
        align(a, b);
        a = eval(a);
        b = eval(b);
        for (int i = 0; i < a.size(); i++) a[i] = a[i] * b[i] % p;
        return inter(a);
    }
} ntt[B];

namespace crt {
    LL mult(LL a, LL b, LL mod) {
        return a * b % mod;
    }

    LL binpow(LL a, LL n, LL mod) {
        LL res = 1;
        while (n) {
            if (n & 1) res = mult(res, a, mod);
            a = mult(a, a, mod);
            n >>= 1;
        }
        return res;
    }

    LL inv(LL a, LL mod) {
        return binpow(a, mod - 2, mod);
    }

    LL calc(LL a, LL p) {
        return a % p;
    }

    LL calc(LL a, LL p, LL b, LL q) {
        return (mult(a, inv(p % q, q), q) * p + mult(b, inv(q % p, p), p) * q) % (p * q);
    }

    LL calc(LL a, LL p, LL b, LL q, LL c, LL r) {
        LL ans = mult(a, inv(q * r % p, p), p) * q * r;
        ans += mult(b, inv(p * r % q, q), q) * p * r;
        ans += mult(c, inv(p * q % r, r), r) * p * q;
        return ans % (p * q * r);
    }
};

void init() {
    for (int i = 0; i < B; i++) {
        ntt[i].init(P[i], G[i]);
    }
}

const int mod = 1e9 + 7;

poly mult(poly a, poly b) {
    vector<poly> res(B);
    for (int j = 0; j < B; j++) {
        res[j] = ntt[j].mult(a, b);
    }
    poly ans(res[0].size());
    if constexpr (B == 1) {
        for (int i = 0; i < ans.size(); i++) {
            ans[i] = crt::calc(res[0][i], P[0]) % mod;
        }
    } else if constexpr (B == 2) {
        for (int i = 0; i < ans.size(); i++) {
            ans[i] = crt::calc(res[0][i], P[0], res[1][i], P[1]) % mod;
        }
    } else {
        for (int i = 0; i < ans.size(); i++) {
            ans[i] = crt::calc(res[0][i], P[0], res[1][i], P[1], res[2][i], P[2]) % mod;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL_ALIKHAN
    freopen("input.txt", "r", stdin);
#endif

    init();

#ifdef LOCAL_ALIKHAN
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}