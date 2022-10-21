#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
 * BE CAREFUL: A LOST OF ASSIRTS || BASE OF PRIMITIVE ROOTS IS TOO SMALL
 * TESTED ON:
 *      https://judge.yosupo.jp/problem/convolution_mod_1000000007
 *      https://codeforces.com/contest/623/problem/E
 *      https://official.contest.yandex.com/mw-2022-fall/contest/41453/problems/H3/?success=72697340#7/2016_03_26/d2ymbyN16k
 */

constexpr int32_t modpow(int64_t x, uint64_t k, int32_t MOD) {
    assert (0 <= x and x < MOD);
    int64_t y = 1;
    for (; k; k >>= 1) {
        if (k & 1) (y *= x) %= MOD;
        (x *= x) %= MOD;
    }
    assert (0 <= y and y < MOD);
    return y;
}
int32_t modinv_nocheck(int32_t value, int32_t MOD) {
    assert (0 <= value and value < MOD);
    if (value == 0) return -1;
    int64_t a = value, b = MOD;
    int64_t x = 0, y = 1;
    for (int64_t u = 1, v = 0; a; ) {
        int64_t q = b / a;
        x -= q * u; std::swap(x, u);
        y -= q * v; std::swap(y, v);
        b -= q * a; std::swap(b, a);
    }
    if (not (value * x + MOD * y == b and b == 1)) return -1;
    if (x < 0) x += MOD;
    assert (0 <= x and x < MOD);
    return x;
}
inline int32_t modinv(int32_t x, int32_t MOD) {
    int32_t y = modinv_nocheck(x, MOD);
    assert (y != -1);
    return y;
}

template <int32_t MOD>
struct mint {
    int32_t value;
    mint() : value() {}
    mint(int64_t value_) : value(value_ < 0 ? value_ % MOD + MOD : value_ >= MOD ? value_ % MOD : value_) {}
    mint(int32_t value_, std::nullptr_t) : value(value_) {}
    explicit operator bool() const { return value; }
    inline constexpr mint<MOD> operator + (mint<MOD> other) const { return mint<MOD>(*this) += other; }
    inline constexpr mint<MOD> operator - (mint<MOD> other) const { return mint<MOD>(*this) -= other; }
    inline constexpr mint<MOD> operator * (mint<MOD> other) const { return mint<MOD>(*this) *= other; }
    inline constexpr mint<MOD> & operator += (mint<MOD> other) { this->value += other.value; if (this->value >= MOD) this->value -= MOD; return *this; }
    inline constexpr mint<MOD> & operator -= (mint<MOD> other) { this->value -= other.value; if (this->value <    0) this->value += MOD; return *this; }
    inline constexpr mint<MOD> & operator *= (mint<MOD> other) { this->value = (uint_fast64_t)this->value * other.value % MOD; return *this; }
    inline constexpr mint<MOD> operator - () const { return mint<MOD>(this->value ? MOD - this->value : 0, nullptr); }
    inline constexpr mint<MOD> pow(uint64_t k) const { return mint<MOD>(modpow(value, k, MOD), nullptr); }
    inline mint<MOD> inv() const { return mint<MOD>(modinv(value, MOD), nullptr); }
    inline constexpr mint<MOD> operator /  (mint<MOD> other) const { return *this *  other.inv(); }
    inline constexpr mint<MOD> operator /= (mint<MOD> other)       { return *this *= other.inv(); }
    inline constexpr bool operator == (mint<MOD> other) const { return value == other.value; }
    inline constexpr bool operator != (mint<MOD> other) const { return value != other.value; }
};
template <int32_t MOD> mint<MOD> operator * (int64_t value, mint<MOD> n) { return mint<MOD>(value) * n; }
template <int32_t MOD> std::istream & operator >> (std::istream & in, mint<MOD> & n) { int64_t value; in >> value; n = value; return in; }
template <int32_t MOD> std::ostream & operator << (std::ostream & out, mint<MOD> n) { return out << n.value; }

template <int32_t PRIME> struct proth_prime {};
template <> struct proth_prime<1224736769> { static constexpr int a =             73, b = 24, g =  3; };
template <> struct proth_prime<1053818881> { static constexpr int a =     3 * 5 * 67, b = 20, g =  7; };
template <> struct proth_prime<1051721729> { static constexpr int a =        17 * 59, b = 20, g =  6; };
template <> struct proth_prime<1045430273> { static constexpr int a =            997, b = 20, g =  3; };
template <> struct proth_prime<1012924417> { static constexpr int a =     3 * 7 * 23, b = 21, g =  5; };
template <> struct proth_prime<1007681537> { static constexpr int a =        31 * 31, b = 20, g =  3; };
template <> struct proth_prime<1004535809> { static constexpr int a =            479, b = 21, g =  3; };
template <> struct proth_prime< 998244353> { static constexpr int a =         7 * 17, b = 23, g =  3; };
template <> struct proth_prime< 985661441> { static constexpr int a =         5 * 47, b = 22, g =  3; };
template <> struct proth_prime< 976224257> { static constexpr int a =     7 * 7 * 19, b = 20, g =  3; };
template <> struct proth_prime< 975175681> { static constexpr int a =     3 * 5 * 31, b = 21, g = 17; };
template <> struct proth_prime< 962592769> { static constexpr int a = 3 * 3 * 3 * 17, b = 21, g =  7; };
template <> struct proth_prime< 950009857> { static constexpr int a =        4 * 151, b = 21, g =  7; };
template <> struct proth_prime< 943718401> { static constexpr int a =  3 * 3 * 5 * 5, b = 22, g =  7; };
template <> struct proth_prime< 935329793> { static constexpr int a =            223, b = 22, g =  3; };
template <> struct proth_prime< 924844033> { static constexpr int a =  3 * 3 * 7 * 7, b = 21, g =  5; };
template <> struct proth_prime< 469762049> { static constexpr int a =              7, b = 26, g =  3; };
template <> struct proth_prime< 167772161> { static constexpr int a =              5, b = 25, g =  3; };

struct is_proth_prime_impl {
    template <int32_t PRIME, class T> static auto check(T *) -> decltype(proth_prime<PRIME>::g, std::true_type());
    template <int32_t PRIME, class T> static auto check(...) -> std::false_type;
};
template <int32_t PRIME>
struct is_proth_prime : decltype(is_proth_prime_impl::check<PRIME, std::nullptr_t>(nullptr)) {
};

template <int32_t PRIME>
void ntt_inplace(std::vector<mint<PRIME> > & a, bool inverse) {
    const int n = a.size();
    const int log2_n = __builtin_ctz(n);
    assert (n == 1 << log2_n);
    assert (log2_n <= proth_prime<PRIME>::b);

    // prepare rotors
    std::vector<mint<PRIME> > ep, iep;
    while ((int)ep.size() <= log2_n) {
        ep.push_back(mint<PRIME>(proth_prime<PRIME>::g).pow(mint<PRIME>(-1).value / (1 << ep.size())));
        iep.push_back(ep.back().inv());
    }

    // divide and conquer
    std::vector<mint<PRIME> > b(n);
    for (int i = 1; i <= log2_n; i++) {
        int w = 1 << (log2_n - i);
        mint<PRIME> base = (inverse ? iep : ep)[i];
        mint<PRIME> now = 1;
        for (int y = 0; y < n / 2; y += w) {
            for (int x = 0; x < w; x++) {
                auto l = a[y << 1 | x];
                auto r = now * a[y << 1 | x | w];
                b[y | x] = l + r;
                b[y | x | n >> 1] = l - r;
            }
            now *= base;
        }
        std::swap(a, b);
    }

    // div by n if inverse
    if (inverse) {
        auto n_inv = mint<PRIME>(n).inv();
        for (int i = 0; i < n; i++) {
            a[i] *= n_inv;
        }
    }
}

template <int32_t PRIME>
typename std::enable_if<is_proth_prime<PRIME>::value, std::vector<mint<PRIME> > >::type ntt_convolution(const std::vector<mint<PRIME> > & a_, const std::vector<mint<PRIME> > & b_) {
    if (a_.size() <= 32 or b_.size() <= 32) {
        std::vector<mint<PRIME> > c(a_.size() + b_.size() - 1);
        for (int i = 0; i < a_.size(); i++) {
            for (int j = 0; j < b_.size(); j++) {
                c[i + j] += a_[i] * b_[j];
            }
        }
        return c;
    }
    int m = a_.size() + b_.size() - 1;
    int n = (m == 1 ? 1 : 1 << (32 - __builtin_clz(m - 1)));
    auto a = a_;
    auto b = b_;
    a.resize(n);
    b.resize(n);
    ntt_inplace(a, false);
    ntt_inplace(b, false);
    for (int i = 0; i < n; i++) {
        a[i] *= b[i];
    }
    ntt_inplace(a, true);
    a.resize(m);
    return a;
}

template <int32_t MOD, int32_t MOD1, int32_t MOD2, int32_t MOD3>
mint<MOD> garner_algorithm_template(mint<MOD1> a1, mint<MOD2> a2, mint<MOD3> a3) {
    static const auto r12 = mint<MOD2>(MOD1).inv();
    static const auto r13 = mint<MOD3>(MOD1).inv();
    static const auto r23 = mint<MOD3>(MOD2).inv();
    a2 = (a2 - a1.value) * r12;
    a3 = (a3 - a1.value) * r13;
    a3 = (a3 - a2.value) * r23;
    return mint<MOD>(a1.value) + a2.value * mint<MOD>(MOD1) + a3.value * (mint<MOD>(MOD1) * mint<MOD>(MOD2));
}

typedef __int128_t LL;

LL lcm(LL a, LL b) { return a / __gcd(a, b) * b; }

LL gcd(LL a, LL b, LL & x, LL & y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    LL x1, y1;
    LL d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

bool find_any_solution(LL a, LL b, LL c, LL& x0, LL& y0) {
    LL A = a, B = b;
    if (A < 0) A *= -1;
    if (B < 0) B *= -1;
    LL g = gcd(A, B, x0, y0);
    if (c % g != 0) return false;
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 *= -1;
    if (b < 0) y0 *= -1;
    return true;
}

LL CRT_2(LL r1, LL mod1, LL r2, LL mod2) {
    LL x, y;
    if (!find_any_solution(mod1, -mod2, r2 - r1, x, y)) {
        return -1;
    }
    LL X = mod1 * x + r1;
    LL tot_mod = lcm(mod1, mod2);
    X = (X % tot_mod + tot_mod) % tot_mod;
    return X;
}

template <int64_t max_val>
bool can_use_two(int64_t a, int64_t b, int64_t c) {
    return !(a > max_val / b || a * b > max_val / c);
}

template <int32_t MOD>
typename std::enable_if<not is_proth_prime<MOD>::value, std::vector<mint<MOD> > >::type
ntt_convolution(const std::vector<mint<MOD> > & a, const std::vector<mint<MOD> > & b) {
    if (a.size() <= 32 or b.size() <= 32) {
        std::vector<mint<MOD> > c(a.size() + b.size() - 1);
        for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < b.size(); j++) {
                c[i + j] += a[i] * b[j];
            }
        }
        return c;
    }
    constexpr int PRIMES[3] = { 1004535809, 998244353, 985661441 };
    // constexpr int PRIMES[3] = {1224736769, 998244353, 469762049};
    if (can_use_two<1ll * PRIMES[0] * PRIMES[1] - 10>(2 * max(a.size(), b.size()) + 1, MOD, MOD)) {
        std::vector<mint<PRIMES[0]> > x0(a.size());
        std::vector<mint<PRIMES[1]> > x1(a.size());
        for (int i = 0; i < a.size(); i++) {
            x0[i] = a[i].value;
            x1[i] = a[i].value;
        }
        std::vector<mint<PRIMES[0]> > y0(b.size());
        std::vector<mint<PRIMES[1]> > y1(b.size());
        for (int j = 0; j < b.size(); j++) {
            y0[j] = b[j].value;
            y1[j] = b[j].value;
        }
        std::vector<mint<PRIMES[0]> > z0 = ntt_convolution<PRIMES[0]>(x0, y0);
        std::vector<mint<PRIMES[1]> > z1 = ntt_convolution<PRIMES[1]>(x1, y1);
        std::vector<mint<MOD> > c(z0.size());
        for (int k = 0; k < z0.size(); k++) {
            c[k] = CRT_2(z0[k].value, PRIMES[0], z1[k].value, PRIMES[1]);
        }
        return c;
    } else {
        std::vector<mint<PRIMES[0]> > x0(a.size());
        std::vector<mint<PRIMES[1]> > x1(a.size());
        std::vector<mint<PRIMES[2]> > x2(a.size());
        for (int i = 0; i < a.size(); i++) {
            x0[i] = a[i].value;
            x1[i] = a[i].value;
            x2[i] = a[i].value;
        }
        std::vector<mint<PRIMES[0]> > y0(b.size());
        std::vector<mint<PRIMES[1]> > y1(b.size());
        std::vector<mint<PRIMES[2]> > y2(b.size());
        for (int j = 0; j < b.size(); j++) {
            y0[j] = b[j].value;
            y1[j] = b[j].value;
            y2[j] = b[j].value;
        }
        std::vector<mint<PRIMES[0]> > z0 = ntt_convolution<PRIMES[0]>(x0, y0);
        std::vector<mint<PRIMES[1]> > z1 = ntt_convolution<PRIMES[1]>(x1, y1);
        std::vector<mint<PRIMES[2]> > z2 = ntt_convolution<PRIMES[2]>(x2, y2);
        std::vector<mint<MOD> > c(z0.size());
        for (int k = 0; k < z0.size(); k++) {
            c[k] = garner_algorithm_template<MOD>(z0[k], z1[k], z2[k]);
        }
        return c;
    }
}

template <int mod, typename T>
vector<mint<mod>> vec_to_mint(const vector<T>& vec) {
    vector<mint<mod>> res(vec.size());
    for (int i = 0; i < vec.size(); i++) {
        res[i] = vec[i];
    }
    return res;
}

template <int mod, typename T = int>
vector<T> mint_to_vec(const vector<mint<mod>>& vec) {
    vector<T> res(vec.size());
    for (int i = 0; i < vec.size(); i++) {
        res[i] = vec[i].value;
    }
    return res;
}

template <int32_t mod, typename T>
typename std::enable_if<is_integral_v<T>, vector<T> >::type
ntt_convolution(const vector<T>& a, const vector<T>& b) {
    return mint_to_vec<mod, T>(ntt_convolution(vec_to_mint<mod>(a), vec_to_mint<mod>(b)));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    constexpr int mod = 1e9 + 7;
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int j = 0; j < m; j++) {
        cin >> b[j];
    }
    vector<int> res = ntt_convolution<mod>(a, b);
    for (auto x : res) {
        cout << x << " ";
    }
    cout << "\n";

#ifdef LOCAL
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
}
