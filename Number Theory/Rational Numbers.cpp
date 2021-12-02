#include <bits/stdc++.h>

using namespace std;

template <typename T = long long>
struct Rational {
    T p, q;
    Rational() : p(0), q(1) {
    }
    Rational(T val) : p(val), q(1) {
    }
    Rational(T num, T den) : p(num), q(den) {
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
        return {p * ot.q + q * ot.p, q * ot.q};
    }
    Rational operator-(const Rational& ot) const {
        return {p * ot.q - q * ot.p, q * ot.q};
    }
    Rational operator*(const Rational& ot) const {
        return {p * ot.p, q * ot.q};
    }
    Rational operator/(const Rational& ot) const {
        return {p * ot.q, q * ot.p};
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