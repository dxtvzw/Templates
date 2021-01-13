#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128_t LL;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

template <typename T>
struct Rational {
    T p, q;
    Rational() {
        p = 0;
        q = 1;
    }
    Rational(T val) {
        p = val;
        q = 1;
    }
    Rational(T num, T den) {
        p = num;
        q = den;
        fix();
    }
    Rational& fix() {
        if (p == 0 || q == 0) {
            p = 0;
            q = 1;
        }
        else {
            T g = __gcd(p, q);
            p /= g;
            q /= g;
            if (q < 0) {
                p = -p;
                q = -q;
            }
        }
        return *this;
    }
    Rational operator-() const {
        return Rational(-p, q);
    }
    Rational operator+(const Rational& ot) const {
        return Rational(p * ot.q + q * ot.p, q * ot.q);
    }
    Rational operator-(const Rational& ot) const {
        return Rational(p * ot.q - q * ot.p, q * ot.q);
    }
    Rational operator*(const Rational& ot) const {
        return Rational(p * ot.p, q * ot.q);
    }
    Rational operator/(const Rational& ot) const {
        return Rational(p * ot.q, q * ot.p);
    }
    Rational& operator+=(const Rational& ot) {
        return *this = *this + ot;
    }
    Rational& operator-=(const Rational& ot) {
        return *this = *this - ot;
    }
    Rational& operator*=(const Rational& ot) {
        return *this = *this * ot;
    }
    Rational& operator/=(const Rational& ot) {
        return *this = *this / ot;
    }
    bool operator==(const Rational& ot) const {
        return p == ot.p && q == ot.q;
    }
    bool operator!=(const Rational& ot) const {
        return p != ot.p || q != ot.q;
    }
    bool operator<(const Rational& ot) const {
        return p * ot.q < q * ot.p;
    }
    bool operator>(const Rational& ot) const {
        return p * ot.q > q * ot.p;
    }
};

template <typename T>
Rational<T> abs(const Rational<T>& r) {
    return {abs(r.p), abs(r.q)};
}

template <typename T>
istream& operator>>(istream& istr, Rational<T>& r) {
    istr >> r.p;
    r.q = 1;
    return istr;
}

template <typename T>
ostream& operator<<(ostream& ostr, const Rational<T>& r) {
    return ostr << "(" << r.p << " / " << r.q << ")";
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
