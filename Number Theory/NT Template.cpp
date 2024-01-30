#include <bits/stdc++.h>

using namespace std;

std::mt19937 rnd;

template<typename T>
struct NT {
    static T add(T a, T b, T mod) {
        if (a + b >= mod) return a + b - mod;
        else return a + b;
    }
    static T mult(T a, T b, T mod) {
        return 1ll * a * b % mod;
    }
    static T binpow(T a, T n, T mod) {
        T res = 1;
        while (n) {
            if (n & 1) res = mult(res, a, mod);
            a = mult(a, a, mod);
            n >>= 1;
        }
        return res;
    }
    static T inv(T a, T mod) {
        return binpow(a, mod - 2, mod);
    }
    static vector<pair<T, int>> prime_fact(T x) {
        vector<pair<T, int>> pf;
        for (int i = 2; i * 1ll * i <= x; i++) {
            if (x % i == 0) {
                int t = 0;
                while (x % i == 0) {
                    x /= i;
                    t++;
                }
                pf.push_back({i, t});
            }
        }
        if (x > 1) {
            pf.push_back({x, 1});
        }
        return pf;
    }
    static T Chinese_Remainder_Theorem_2(T rp, T p, T rq, T q) {
        return add(mult(rq, inv(p % q, q), q) * p, mult(rp, inv(q % p, p), p) * q, p * q);
    }
    static T phi(T n) {
        T res = n;
        for (int i = 2; 1ll * i * i <= n; i++) {
            if (n % i == 0) {
                while (n % i == 0) n /= i;
                res -= res / i;
            }
        }
        if (n > 1) res -= res / n;
        return res;
    }
    static T ord(T a, T n) {
        a %= n;
        if (__gcd(a, n) != 1) return 0;
        else if (a == 1) return 1;
        T phi_n = phi(n);
        T ans = phi_n;
        for (int i = 2; i * i <= phi_n; i++) {
            if (phi_n % i == 0) {
                if (binpow(a, i, n) == 1) {
                    ans = min(ans, i);
                }
                if (binpow(a, phi_n / i, n) == 1) {
                    ans = min(ans, phi_n / i);
                }
            }
        }
        return ans;
    }
    static T gen_prim_root(T n) {
        if (n == 2) return 2;
        T phi_n = phi(n);
        vector<pair<T, int>> pf = prime_fact(phi_n);
        for (T g = 1; g <= n - 1; g++) {
            bool ok = true;
            for (int i = 0; i < pf.size() && ok; i++) {
                ok &= binpow(g, phi_n / pf[i].first, n) != 1;
            }
            if (ok) return g;
        }
    }
    static int lagr_sym(T a, T p) {
        a %= p;
        if (a == 0) return 0;
        else if (binpow(a, (p - 1) / 2, p) == 1) return 1;
        else return -1;
    }
    static vector<T> sqrt_mod(T a, T p) {
        a %= p;
        if (p == 2) return {1};
        if (lagr_sym(a, p) == -1) {
            return {};
        }
        T b;
        do {
            b = rnd() % (p - 1) + 1;
        } while (lagr_sym(b, p) == 1);
        T s = 0, t = p - 1;
        while (!(t & 1)) {
            s++;
            t >>= 1;
        }
        T a_inv = binpow(a, p - 2, p);
        T c = binpow(b, t, p);
        T r = binpow(a, (t + 1) / 2, p);
        for (int i = 1; i <= s - 1; i++) {
            if (binpow(mult(mult(r, r, p), a_inv, p), (1 << (s - i - 1)), p) == p - 1) {
                r = mult(r, c, p);
            }
            c = mult(c, c, p);
        }
        return {min(r, p - r), max(r, p - r)};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL_ALIKHAN
    freopen("input.txt", "r", stdin);
#endif

    cout << NT<long long>::lagr_sym(3, 1007) << "\n";

#ifdef LOCAL_ALIKHAN
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}