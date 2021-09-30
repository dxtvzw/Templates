#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128_t LL;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define F first
#define S second
#define pb push_back
mt19937 rnd(time(0));

#define nan my_nan

typedef double real_t;
const real_t eps = 1e-9;
const real_t inf = 1e18 + 10;
const real_t nan = inf + inf + 123123;
const real_t pi = acos(-1);
const long long mult_const = 2;

real_t rand_real(real_t l = 0, real_t r = 1e9, real_t coef = 1000) {
    real_t res = rnd() % ll((r - l) * coef);
    return l + res / coef;
}

bool are_eq(real_t a, real_t b) {
    return abs(a - b) < eps;
}

template <typename T>
struct Point {
    T x, y, z;
    Point& fit() {
        x *= mult_const;
        y *= mult_const;
        z *= mult_const;
        return *this;
    }
    Point operator+(const Point& ot) const {
        return {x + ot.x, y + ot.y, z + ot.z};
    }
    Point operator-(const Point& ot) const {
        return {x - ot.x, y - ot.y, z - ot.z};
    }
    Point operator*(T val) const {
        return {x * val, y * val, z * val};
    }
    Point operator/(T val) const {
        return {x / val, y / val, z / val};
    }
    Point& operator+=(const Point& ot) {
        return *this = *this + ot;
    }
    Point& operator-=(const Point& ot) {
        return *this = *this - ot;
    }
    Point& operator*=(T val) {
        return *this = *this * val;
    }
    Point& operator/=(T val) {
        return *this = *this / val;
    }
    bool operator<(const Point& ot) const {
        return std::tie(x, y, z) < std::tie(ot.x, ot.y, ot.z);
    }
    bool operator>(const Point& ot) const {
        return std::tie(x, y, z) > std::tie(ot.x, ot.y, ot.z);
    }
    // operators if T is an integer type
    bool operator==(const Point& ot) const {
        return x == ot.x && y == ot.y && z == ot.z;
    }
    bool operator!=(const Point& ot) const {
        return x != ot.x || y != ot.y || z != ot.z;
    }
    // operators if T is not an integer type
    /*
    bool operator==(const Point& ot) const {
        return are_eq(x, ot.x) && are_eq(y, ot.y);
    }
    bool operator!=(const Point& ot) const {
        return !are_eq(x, ot.x) || !are_eq(y, ot.y);
    }
    */
};

typedef pair<Point<real_t>, Point<real_t>> ppp;
const Point<real_t> nap = {nan, nan};

template <typename T>
istream& operator>>(istream& istr, Point<T>& p) {
    return istr >> p.x >> p.y >> p.z;
}

template <typename T>
ostream& operator<<(ostream& ostr, const Point<T>& p) {
    return ostr << "(" << p.x << ", " << p.y << ", " << p.z << ")";
}

template <typename T>
struct Circle {
    Point<T> o;
    T r;
};

template <typename T>
istream& operator>>(istream& istr, Circle<T>& w) {
    return istr >> w.o >> w.r;
}

template <typename T>
ostream& operator<<(ostream& ostr, const Circle<T>& w) {
    return ostr << "{" << w.o << " : " << w.r << "}";
}

template <typename T>
T dist2(Point<T> a, Point<T> b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
}

template <typename T>
real_t dist(Point<T> a, Point<T> b) {
    return sqrt(real_t((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z)));
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
