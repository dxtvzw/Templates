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

class Complex {
private:
    double R, I;

public:
    explicit Complex(const double& _R) : R(_R), I(0) {
    }
    Complex(const double& _R, const double& _I) : R(_R), I(_I) {
    }
    double Re() const {
        return R;
    }
    double Im() const {
        return I;
    }
    Complex operator+() const {
        return *this;
    }
    Complex operator-() const {
        return {-R, -I};
    }
    bool operator==(const Complex& ot) const {
        return R == ot.R && I == ot.I;
    }
    bool operator!=(const Complex& ot) const {
        return !(*this == ot);
    }
};

double abs(const Complex& a) {
    return sqrt(a.Re() * a.Re() + a.Im() * a.Im());
}

Complex operator+(const Complex& a, const Complex& b) {
    return {a.Re() + b.Re(), a.Im() + b.Im()};
}

Complex operator+(const double& a, const Complex& b) {
    return Complex(a) + b;
}

Complex operator+(const Complex& a, const double& b) {
    return a + Complex(b);
}

Complex operator-(const Complex& a, const Complex& b) {
    return {a.Re() - b.Re(), a.Im() - b.Im()};
}

Complex operator-(const double& a, const Complex& b) {
    return Complex(a) - b;
}

Complex operator-(const Complex& a, const double& b) {
    return a - Complex(b);
}

Complex operator*(const Complex& a, const Complex& b) {
    return {
        a.Re() * b.Re() - a.Im() * b.Im(),
        a.Re() * b.Im() + a.Im() * b.Re()
    };
}

Complex operator*(const double& a, const Complex& b) {
    return Complex(a) * b;
}

Complex operator*(const Complex& a, const double& b) {
    return a * Complex(b);
}

Complex operator/(const Complex& a, const Complex& b) {
    return {
        (a.Re() * b.Re() + a.Im() * b.Im()) / (abs(b) * abs(b)),
        (a.Im() * b.Re() - a.Re() * b.Im()) / (abs(b) * abs(b))
    };
}

Complex operator/(const double& a, const Complex& b) {
    return Complex(a) / b;
}

Complex operator/(const Complex& a, const double& b) {
    return a / Complex(b);
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
