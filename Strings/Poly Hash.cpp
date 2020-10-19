#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

template<int mod>
class Modular {
public:
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
    static const int N = 1e6 + 10;
    static const int V = 1000;
    Modular<mod> p = rnd() % int(sqrt(mod)) + V;
    Modular<mod> pw[N];
    Modular<mod> pref[N];
    void init(int n, vector<int> a) {
        pw[0] = 1;
        for (int i = 1; i <= n; i++) {
            pref[i] = pref[i - 1] * p + a[i];
            pw[i] = pw[i - 1] * p;
        }
    }
    Modular<mod> get(int l, int r) {
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
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif



#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
   return 0;
}
