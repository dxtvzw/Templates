#include <bits/stdc++.h>

using namespace std;

template<int mod>
class Modular {
public:
    int val;
    Modular() : val(0) {}
    Modular(int new_val) : val(new_val) {
    }
    Modular(long long new_val) : val(new_val % mod) {
    }
    friend Modular operator+(const Modular& a, const Modular& b) {
        if (a.val + b.val >= mod) return a.val + b.val - mod;
        else return a.val + b.val;
    }
    friend Modular operator-(const Modular& a, const Modular& b) {
        if (a.val - b.val < 0) return a.val - b.val + mod;
        else return a.val - b.val;
    }
    friend Modular operator*(const Modular& a, const Modular& b) {
        return 1ll * a.val * b.val % mod;
    }
    friend Modular binpow(Modular a, long long n) {
        Modular res = 1;
        for (; n; n >>= 1) {
            if (n & 1) res *= a;
            a *= a;
        }
        return res;
    }
    /* ALTERNATIVE INVERSE FUNCTION USING EXTENDED EUCLIDEAN ALGORITHM
    friend void gcd(int a, int b, Modular& x, Modular& y) {
        if (a == 0) {
            x = Modular(0);
            y = Modular(1);
            return;
        }
        Modular x1, y1;
        gcd(b % a, a, x1, y1);
        x = y1 - (b / a) * x1;
        y = x1;
    }
    friend Modular inv(const Modular& a) {
        Modular x, y;
        gcd(a.val, mod, x, y);
        return x;
    }
    */
    friend Modular inv(const Modular& a) {
        return binpow(a, mod - 2);
    }
    Modular operator/(const Modular& ot) const {
        return *this * inv(ot);
    }
    Modular& operator++() {
        if (val + 1 == mod) val = 0;
        else ++val;
        return *this;
    }
    Modular operator++(int) {
        Modular tmp = *this;
        ++(*this);
        return tmp;
    }
    Modular operator+() const {
        return *this;
    }
    Modular operator-() const {
        return 0 - *this;
    }
    Modular& operator+=(const Modular& ot) {
        return *this = *this + ot;
    }
    Modular& operator-=(const Modular& ot) {
        return *this = *this - ot;
    }
    Modular& operator*=(const Modular& ot) {
        return *this = *this * ot;
    }
    Modular& operator/=(const Modular& ot) {
        return *this = *this / ot;
    }
    bool operator==(const Modular& ot) const {
        return val == ot.val;
    }
    bool operator!=(const Modular& ot) const {
        return val != ot.val;
    }
    bool operator<(const Modular& ot) const {
        return val < ot.val;
    }
    bool operator>(const Modular& ot) const {
        return val > ot.val;
    }
    explicit operator int() const {
        return val;
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

const int mod = 1000000007; // 998244353
using Mint = Modular<mod>;

const int N = 2e5 + 10;
Mint fact[N], inv_fact[N], pw2[N], pw3[N];

void init() {
    fact[0] = pw2[0] = pw3[0] = 1;
    for (int i = 1; i <= N - 1; i++) {
        fact[i] = fact[i - 1] * i;
        pw2[i] = pw2[i - 1] + pw2[i - 1];
        pw3[i] = pw3[i - 1] + pw3[i - 1] + pw3[i - 1];
    }
    inv_fact[N - 1] = inv(fact[N - 1]);
    for (int i = N - 2; i >= 0; i--) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1);
    }
}

Mint C(int n, int k) {
    if (n < 0 || k < 0 || n < k) return 0;
    return fact[n] * inv_fact[k] * inv_fact[n - k];
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