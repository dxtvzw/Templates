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
mt19937 rnd(time(0));

template <typename T>
class ConstPolyIter;

template <typename T>
class Polynomial {
private:
    const T zero = T(0);
    std::vector<T> poly;
    Polynomial& fix_size() {
        while (!poly.empty() && poly.back() == T(0)) {
            poly.pop_back();
        }
        return *this;
    }

public:
    explicit Polynomial(const std::vector<T>& _poly) {
        poly = _poly;
        fix_size();
    }
    explicit Polynomial(const T& c = T(0)) {
        poly = {c};
        fix_size();
    }
    template <typename Iter>
    Polynomial(Iter first, Iter last) {
        while (first != last) {
            poly.push_back(*first++);
        }
        fix_size();
    }
    Polynomial(const Polynomial& ot) {
        poly.resize(ot.Degree() + 1);
        for (int i = 0; i <= ot.Degree(); ++i) {
            poly[i] = ot[i];
        }
        fix_size();
    }
    Polynomial(Polynomial&& ot) {
        poly.resize(ot.Degree() + 1);
        for (int i = 0; i <= ot.Degree(); ++i) {
            poly[i] = ot[i];
        }
        fix_size();
    }
    Polynomial& operator=(const Polynomial& ot) {
        poly.resize(ot.Degree() + 1);
        for (int i = 0; i <= ot.Degree(); ++i) {
            poly[i] = ot[i];
        }
        fix_size();
        return *this;
    }
    bool operator==(const Polynomial& ot) const {
        if (Degree() != ot.Degree()) {
            return false;
        } else {
            for (int i = 0; i <= Degree(); ++i) {
                if ((*this)[i] != ot[i]) {
                    return false;
                }
            }
            return true;
        }
    }
    bool operator!=(const Polynomial& ot) const {
        return !(*this == ot);
    }
    friend bool operator==(const Polynomial<T>& a, const T& b) {
        return a == Polynomial<T>(b);
    }
    friend bool operator==(const T& a, const Polynomial<T>& b) {
        return Polynomial<T>(a) == b;
    }
    friend bool operator!=(const Polynomial<T>& a, const T& b) {
        return a != Polynomial<T>(b);
    }
    friend bool operator!=(const T& a, const Polynomial<T>& b) {
        return Polynomial<T>(a) != b;
    }
    Polynomial operator+(const Polynomial& ot) const {
        Polynomial res = *this;
        if (res.Degree() < ot.Degree()) {
            res.poly.resize(ot.Degree() + 1);
        }
        for (int i = 0; i <= ot.Degree(); ++i) {
            res.poly[i] += ot[i];
        }
        return res.fix_size();
    }
    Polynomial operator-(const Polynomial& ot) const {
        Polynomial res = *this;
        if (res.Degree() < ot.Degree()) {
            res.poly.resize(ot.Degree() + 1);
        }
        for (int i = 0; i <= ot.Degree(); ++i) {
            res.poly[i] -= ot[i];
        }
        return res.fix_size();
    }
    Polynomial operator*(const Polynomial& ot) const {
        if (Degree() == -1 || ot.Degree() == -1) {
            return Polynomial(T(0));
        } else {
            Polynomial res;
            res.poly.resize(Degree() + ot.Degree() + 1);
            for (int i = 0; i <= Degree(); ++i) {
                for (int j = 0; j <= ot.Degree(); ++j) {
                    res.poly[i + j] += poly[i] * ot.poly[j];
                }
            }
            return res;
        }
    }
    friend Polynomial<T> operator+(const Polynomial<T>& a, const T& b) {
        return a + Polynomial<T>(b);
    }
    friend Polynomial<T> operator+(const T& a, const Polynomial<T>& b) {
        return Polynomial<T>(a) + b;
    }
    friend Polynomial<T> operator-(const Polynomial<T>& a, const T& b) {
        return a - Polynomial<T>(b);
    }
    friend Polynomial<T> operator-(const T& a, const Polynomial<T>& b) {
        return Polynomial<T>(a) - b;
    }
    friend Polynomial<T> operator*(const Polynomial<T>& a, const T& b) {
        return a * Polynomial<T>(b);
    }
    friend Polynomial<T> operator*(const T& a, const Polynomial<T>& b) {
        return Polynomial<T>(a) * b;
    }
    Polynomial& operator+=(const Polynomial& ot) {
        return *this = *this + ot;
    }
    Polynomial& operator+=(const T& ot) {
        return *this += Polynomial(ot);
    }
    Polynomial& operator-=(const Polynomial& ot) {
        return *this = *this - ot;
    }
    Polynomial& operator-=(const T& ot) {
        return *this -= Polynomial(ot);
    }
    Polynomial& operator*=(const Polynomial& ot) {
        return *this = *this * ot;
    }
    Polynomial& operator*=(const T& ot) {
        return *this *= Polynomial(ot);
    }
    const T& operator[](int i) const {
        if (i > Degree()) {
            return zero;
        } else {
            return poly[i];
        }
    }
    bool Empty() const {
        return poly.empty();
    }
    int Degree() const {
        if (Empty()) {
            return -1;
        } else {
            return poly.size() - 1;
        }
    }
    T operator()(const T& val) const {
        T res = T(0);
        T pw = 1;
        for (int i = 0; i <= Degree(); ++i) {
            res += poly[i] * pw;
            pw *= val;
        }
        return res;
    }
    ConstPolyIter<T> begin() const {
        return ConstPolyIter<T>(*this, 0);
    }
    ConstPolyIter<T> end() const {
        return ConstPolyIter<T>(*this, Degree() + 1);
    }
    Polynomial operator&(const Polynomial& ot) const {
        if (Degree() == -1) {
            return *this;
        } else if (ot.Degree() == -1) {
            return Polynomial(poly[0]);
        } else {
            Polynomial res(0);
            Polynomial pw(1);
            for (int i = 0; i <= Degree(); ++i) {
                res += poly[i] * pw;
                pw *= ot;
            }
            return res;
        }
    }
    const T& back() const {
        return poly.back();
    }
    Polynomial shift(int d) const {
        if (Degree() == -1 || d == 0) {
            return *this;
        } else {
            Polynomial res(*this);
            res.poly.resize(res.poly.size() + d);
            for (int i = res.Degree(); i >= d; --i) {
                res.poly[i] = res[i - d];
            }
            for (int i = d - 1; i >= 0; --i) {
                res.poly[i] = T(0);
            }
            return res;
        }
    }
};

template<typename T>
Polynomial<T> x_to_nth_power(int n) {
    if (n < 0) {
        return Polynomial<T>();
    } else {
        std::vector<T> coefficients(n + 1, T(0));
        coefficients[n] = T(1);
        return Polynomial(coefficients);
    }
}

template<typename T>
std::pair<Polynomial<T>, Polynomial<T>>
divide(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    Polynomial<T> result, remainder(lhs);
    for (int power = lhs.Degree(); power >= rhs.Degree(); --power) {
        const auto to_subtract = (remainder[power] / rhs[rhs.Degree()])
                                 * x_to_nth_power<T>(power - rhs.Degree());
        remainder -= to_subtract * rhs;
        result += to_subtract;
    }
    return {result, remainder};
}

template<typename T>
Polynomial<T> operator/(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    const auto [d, _] = divide(lhs, rhs);
    return d;
}

template<typename T>
Polynomial<T> operator/=(Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    lhs = lhs / rhs;
    return lhs;
}

template<typename T>
Polynomial<T> operator/=(Polynomial<T>& lhs, const T& rhs) {
    lhs = lhs / Polynomial(rhs);
    return lhs;
}

template<typename T>
Polynomial<T> operator%(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    const auto [_, r] = divide(lhs, rhs);
    return r;
}

template<typename T>
Polynomial<T> operator%=(Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    lhs = lhs % rhs;
    return lhs;
}

template<typename T>
Polynomial<T> operator,(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    auto a(lhs), b(rhs);
    while (b.Degree() >= 0) {
        a %= b;
        std::swap(a, b);
    }
    if (a.Degree() >= 0) {
        auto leading_coefficient = a[a.Degree()];
        a /= leading_coefficient;
    }
    return a;
}

template <typename T>
std::ostream& operator<<(std::ostream& ostr, const Polynomial<T>& p) {
    if (p.Degree() == -1) {
        ostr << "0";
    } else {
        for (int i = p.Degree(); i >= 0; --i) {
            if (p[i] < T(0)) {
                ostr << "-";
                if (p[i] == T(-1)) {
                    if (i > 0) {
                        ostr << "x";
                        if (i > 1) {
                            ostr << "^" << i;
                        }
                    } else {
                        ostr << "1";
                    }
                } else {
                    if (i > 0) {
                        ostr << -p[i] << "*x";
                        if (i > 1) {
                            ostr << "^" << i;
                        }
                    } else {
                        ostr << -p[i];
                    }
                }
            } else if (p[i] > T(0)) {
                if (i < p.Degree()) {
                    ostr << "+";
                }
                if (p[i] == T(1)) {
                    if (i > 0) {
                        ostr << "x";
                        if (i > 1) {
                            ostr << "^" << i;
                        }

                    } else {
                        ostr << "1";
                    }
                } else {
                    if (i > 0) {
                        ostr << p[i] << "*x";
                        if (i > 1) {
                            ostr << "^" << i;
                        }
                    } else {
                        ostr << p[i];
                    }
                }
            }
        }
    }
    return ostr;
}

template <typename T>
class ConstPolyIter {
private:
    const Polynomial<T>& p;
    int ptr;

public:
    explicit ConstPolyIter(const Polynomial<T>& _p, int _ptr) : p(_p), ptr(_ptr) {}
    ConstPolyIter& operator++() {
        ++ptr;
        return *this;
    }
    ConstPolyIter& operator--() {
        --ptr;
        return *this;
    }
    ConstPolyIter& operator+(int x) {
        ptr += x;
        return *this;
    }
    ConstPolyIter& operator-(int x) {
        ptr -= x;
        return *this;
    }
    const T& operator*() const {
        return p[ptr];
    }
    bool operator==(const ConstPolyIter& ot) const {
        return ptr == ot.ptr;
    }
    bool operator!=(const ConstPolyIter& ot) const {
        return ptr != ot.ptr;
    }
};

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
