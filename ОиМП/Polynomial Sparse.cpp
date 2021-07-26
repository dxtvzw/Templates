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

template<typename T>
T quick_power(const T& point, size_t power) {
    if (power == 0) {
        return T(1);
    } else if (power % 2 != 0) {
        return quick_power(point, power - 1) * point;
    } else {
        T tmp = quick_power(point, power / 2);
        return tmp * tmp;
    }
}

template<typename T>
class Polynomial {
    static inline T global_zero = T(0);
    std::map<size_t, T> coefficients;

    void remove_zeros() {
        std::vector<size_t> zeros;
        for (const auto& [power, coefficient] : coefficients) {
            if (coefficient == T(0)) {
                zeros.emplace_back(power);
            }
        }
        for (size_t power : zeros) {
            coefficients.erase(power);
        }
    }

public:
    static Polynomial<T> x_to_nth_power(size_t n) {
        Polynomial result;
        result.coefficients[n] = 1;
        return result;
    }

    Polynomial(const std::vector<T>& c) {
        for (size_t i = 0; i < c.size(); ++i) {
            if (c[i] != T(0)) {
                coefficients[i] = c[i];
            }
        }
    }

    Polynomial(const T& v) {
        if (v != T(0)) {
            coefficients[0] = v;
        }
    }

    Polynomial() {
    }

    template<typename Iter>
    Polynomial(Iter begin, Iter end) {
        size_t i = 0;
        while (begin != end) {
            if (*begin != T(0)) {
                coefficients[i] = *begin;
            }
            ++begin;
            ++i;
        }
    }

    bool operator==(const Polynomial& other) const {
        return coefficients == other.coefficients;
    }

    bool operator==(const T& other) const {
        return (*this) == Polynomial(other);
    }

    bool operator!=(const Polynomial& other) const {
        return coefficients != other.coefficients;
    }

    bool operator!=(const T& other) const {
        return (*this) != Polynomial(other);
    }

    Polynomial& operator+=(const Polynomial& other) {
        for (const auto& [power, coefficient] : other.coefficients) {
            coefficients[power] += coefficient;
        }
        remove_zeros();
        return *this;
    }

    Polynomial& operator-=(const Polynomial& other) {
        for (const auto& [power, coefficient] : other.coefficients) {
            coefficients[power] -= coefficient;
        }
        remove_zeros();
        return *this;
    }

    Polynomial& operator*=(const Polynomial& other) {
        std::map<size_t, T> new_coefficients;
        for (const auto& [power1, coefficient1] : coefficients) {
            for (const auto& [power2, coefficient2] : other.coefficients) {
                new_coefficients[power1 + power2] += coefficient1 * coefficient2;
            }
        }
        coefficients = new_coefficients;
        remove_zeros();
        return *this;
    }

    Polynomial& operator+=(const T& ot) {
        (*this) += Polynomial(ot);
        return *this;
    }

    Polynomial& operator-=(const T& ot) {
        (*this) -= Polynomial(ot);
        return *this;
    }

    Polynomial& operator*=(const T& ot) {
        (*this) *= Polynomial(ot);
        return *this;
    }

    const T& operator[](size_t i) const {
        const auto iter = coefficients.find(i);
        if (iter == coefficients.end()) {
            return global_zero;
        } else {
            return iter->second;
        }
    }

    long long int Degree() const {
        if (coefficients.empty()) {
            return -1;
        } else {
            return static_cast<long long int>(coefficients.rbegin()->first);
        }
    }

    template<typename Point>
    Point operator()(const Point& point) const {
        Point result(0);
        for (const auto& [power, coefficient] : coefficients) {
            result += coefficient * quick_power(point, power);
        }
        return result;
    }

    typename std::map<size_t, T>::const_iterator begin() const {
        return coefficients.begin();
    }

    typename std::map<size_t, T>::const_iterator end() const {
        return coefficients.end();
    }

    std::pair<Polynomial<T>, Polynomial<T>>
    divide(const Polynomial<T>& other) const {
        Polynomial<T> result, remainder(*this);
        while (remainder.Degree() >= other.Degree()) {
            const auto coefficient = (remainder[remainder.Degree()] / other[other.Degree()]);
            const auto power = remainder.Degree() - other.Degree();
            const auto to_subtract = coefficient * Polynomial<T>::x_to_nth_power(power);
            remainder -= to_subtract * other;
            result += to_subtract;
        }
        return {result, remainder};
    }

    void print(std::ostream& out) const {
        const T zero(0);
        const T one(1);
        const T negative_one(-1);
        if (coefficients.empty()) {
            out << "0";
        } else {
            bool first = true;
            for (auto iter = coefficients.rbegin();
                iter != coefficients.rend();
                ++iter) {
                const auto power = iter->first;
                const auto coefficient = iter->second;
                if (coefficient != zero) {
                    if (coefficient > zero) {
                        if (!first) {
                            out << "+";
                        }
                        if (coefficient != one || power == 0) {
                            out << coefficient;
                            if (power != 0) {
                                out << "*";
                            }
                        }
                    } else {
                        if (coefficient == negative_one && power != 0) {
                            out << "-";
                        } else {
                            out << coefficient;
                            if (power != 0) {
                                out << "*";
                            }
                        }
                    }
                    if (power > 1) {
                        out << "x^" << power;
                    } else if (power == 1) {
                        out << "x";
                    }
                    first = false;
                }
            }
        }
    }
};

template<typename T>
Polynomial<T> operator+(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    Polynomial tmp(lhs);
    tmp += rhs;
    return tmp;
}

template<typename T>
Polynomial<T> operator+(const Polynomial<T>& lhs, const T& rhs) {
    return lhs + Polynomial<T>(rhs);
}

template<typename T>
Polynomial<T> operator+(const T& lhs, const Polynomial<T>& rhs) {
    return Polynomial<T>(lhs) + rhs;
}

template<typename T>
Polynomial<T> operator-(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    Polynomial tmp(lhs);
    tmp -= rhs;
    return tmp;
}

template<typename T>
Polynomial<T> operator-(const Polynomial<T>& lhs, const T& rhs) {
    return lhs - Polynomial<T>(rhs);
}

template<typename T>
Polynomial<T> operator-(const T& lhs, const Polynomial<T>& rhs) {
    return Polynomial<T>(lhs) - rhs;
}

template<typename T>
Polynomial<T> operator*(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    Polynomial tmp(lhs);
    tmp *= rhs;
    return tmp;
}

template<typename T>
Polynomial<T> operator*(const Polynomial<T>& lhs, const T& rhs) {
    return lhs * Polynomial<T>(rhs);
}

template<typename T>
Polynomial<T> operator*(const T& lhs, const Polynomial<T>& rhs) {
    return Polynomial<T>(lhs) * rhs;
}

template<typename T>
Polynomial<T> operator&(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    return lhs(rhs);
}

template<typename T>
Polynomial<T> operator/(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    const auto [d, _] = lhs.divide(rhs);
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
    const auto [_, r] = lhs.divide(rhs);
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

template<typename T>
std::ostream& operator<<(std::ostream& out, const Polynomial<T>& polynomial) {
    polynomial.print(out);
    return out;
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
