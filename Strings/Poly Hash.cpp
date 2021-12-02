#include <bits/stdc++.h>

using namespace std;

template<int mod>
class Modular {
public:
    int val;
    Modular() : val(0) {}
    Modular(int new_val) : val(new_val) {
        assert(0 <= val && val < mod);
#warning DELETE THIS ASSERT
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

template <int mod>
struct PolyHash {
    int N;
    std::mt19937 rnd;
    Modular<mod> p = rnd() % 10000 + 1000;
    vector<Modular<mod>> pw;
    vector<Modular<mod>> pref;
    template <typename container>
    void init(const container& a) {
        int n = a.size();
        pw.resize(n + 1, 0);
        pref.resize(n + 1, 0);
        pw[0] = 1;
        for (int i = 1; i <= n; i++) {
            pref[i] = pref[i - 1] * p + a[i - 1];
            pw[i] = pw[i - 1] * p;
        }
    }
    Modular<mod> get(int l, int r) {
        ++l, ++r;
        return pref[r] - pref[l - 1] * pw[r - l + 1];
    }
};

const int m1 = 1000000123;
const int m2 = 1000000321;
const int m3 = 5000101;
const int m4 = 7000003;
const int m5 = 5003;
const int m6 = 6007;

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