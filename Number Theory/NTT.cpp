#include <bits/stdc++.h>

using namespace std;

template<int mod>
class Modular {
public:
    int val;
    Modular() : val(0) {}
    Modular(int new_val) : val(new_val) {
    }
    friend Modular operator+(const Modular &a, const Modular &b) {
        if (a.val + b.val >= mod) return a.val + b.val - mod;
        else return a.val + b.val;
    }
    friend Modular operator-(const Modular &a, const Modular &b) {
        if (a.val - b.val < 0) return a.val - b.val + mod;
        else return a.val - b.val;
    }
    friend Modular operator*(const Modular &a, const Modular &b) {
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
    friend Modular inv(const Modular &a) {
        return binpow(a, mod - 2);
    }
    Modular operator/(const Modular &ot) const {
        return *this * inv(ot);
    }
    Modular &operator++() {
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
    Modular &operator+=(const Modular &ot) {
        return *this = *this + ot;
    }
    Modular &operator-=(const Modular &ot) {
        return *this = *this - ot;
    }
    Modular &operator*=(const Modular &ot) {
        return *this = *this * ot;
    }
    Modular &operator/=(const Modular &ot) {
        return *this = *this / ot;
    }
    bool operator==(const Modular &ot) const {
        return val == ot.val;
    }
    bool operator!=(const Modular &ot) const {
        return val != ot.val;
    }
    bool operator<(const Modular &ot) const {
        return val < ot.val;
    }
    bool operator>(const Modular &ot) const {
        return val > ot.val;
    }
    explicit operator int() const {
        return val;
    }
};

template<int mod>
istream &operator>>(istream &istr, Modular<mod> &x) {
    return istr >> x.val;
}

template<int mod>
ostream &operator<<(ostream &ostr, const Modular<mod> &x) {
    return ostr << x.val;
}

template <int mod = 998244353, int root = 3>
class NTT {
    using Mint = Modular<mod>;
public:
    static vector<int> mult(const vector<int>& a, const vector<int>& b) {
        vector<Mint> amod(a.size());
        vector<Mint> bmod(b.size());
        for (int i = 0; i < a.size(); i++) {
            amod[i] = a[i];
        }
        for (int i = 0; i < b.size(); i++) {
            bmod[i] = b[i];
        }
        vector<Mint> resmod = mult(amod, bmod);
        vector<int> res(resmod.size());
        for (int i = 0; i < res.size(); i++) {
            res[i] = resmod[i].val;
        }
        return res;
    }
    static vector<Mint> mult(const vector<Mint>& a, const vector<Mint>& b) {
        int n = int(a.size()), m = int(b.size());
        if (!n || !m) return {};
        int lg = 0;
        while ((1 << lg) < n + m - 1) lg++;
        int z = 1 << lg;
        auto a2 = a, b2 = b;
        a2.resize(z);
        b2.resize(z);
        nft(false, a2);
        nft(false, b2);
        for (int i = 0; i < z; i++) a2[i] *= b2[i];
        nft(true, a2);
        a2.resize(n + m - 1);
        Mint iz = inv(Mint(z));
        for (int i = 0; i < n + m - 1; i++) a2[i] *= iz;
        return a2;
    }

private:
    static void nft(bool type, vector<Modular<mod>> &a) {
        int n = int(a.size()), s = 0;
        while ((1 << s) < n) s++;
        assert(1 << s == n);
        static vector<Mint> ep, iep;
        while (int(ep.size()) <= s) {
            ep.push_back(binpow(Mint(root), (mod - 1) / (1 << ep.size())));
            iep.push_back(inv(ep.back()));
        }
        vector<Mint> b(n);
        for (int i = 1; i <= s; i++) {
            int w = 1 << (s - i);
            Mint base = type ? iep[i] : ep[i], now = 1;
            for (int y = 0; y < n / 2; y += w) {
                for (int x = 0; x < w; x++) {
                    auto l = a[y << 1 | x];
                    auto r = now * a[y << 1 | x | w];
                    b[y | x] = l + r;
                    b[y | x | n >> 1] = l - r;
                }
                now *= base;
            }
            swap(a, b);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL_ALIKHAN
    freopen("input.txt", "r", stdin);
#endif



#ifdef LOCAL_ALIKHAN
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
}
