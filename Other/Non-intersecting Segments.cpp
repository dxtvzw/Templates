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

typedef long double real_t;
const real_t eps = 1e-9;
const real_t inf = 1e18 + 10;
const real_t nan = inf + inf + 123123;
const real_t pi = acos(-1);
const long long mult_const = 2;

real_t rand_real(real_t l = 0, real_t r = 1e9, real_t coef = 100000) {
    real_t res = rnd() % ll((r - l) * coef);
    return l + res / coef;
}

bool are_eq(real_t a, real_t b) {
    return abs(a - b) < eps;
}

template <typename T>
struct Point {
    T x, y;
    int id;
    Point& fit() {
        x *= mult_const;
        y *= mult_const;
        return *this;
    }
    Point operator+(const Point& ot) const {
        return {x + ot.x, y + ot.y};
    }
    Point operator-(const Point& ot) const {
        return {x - ot.x, y - ot.y};
    }
    Point operator*(T val) const {
        return {x * val, y * val};
    }
    Point operator/(T val) const {
        return {x / val, y / val};
    }
    Point operator*(const Point& ot) const {
        return {x * ot.x - y * ot.y, x * ot.y + y * ot.x};
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
    Point& operator*=(const Point& ot) {
        return *this = *this * ot;
    }
    bool operator<(const Point& ot) const {
        return std::tie(x, y) < std::tie(ot.x, ot.y);
    }
    bool operator>(const Point& ot) const {
        return std::tie(x, y) > std::tie(ot.x, ot.y);
    }
    // operators if T is an integer type
    bool operator==(const Point& ot) const {
        return x == ot.x && y == ot.y;
    }
    bool operator!=(const Point& ot) const {
        return x != ot.x || y != ot.y;
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

template <typename T>
istream& operator>>(istream& istr, Point<T>& p) {
    return istr >> p.x >> p.y;
}

template <typename T>
ostream& operator<<(ostream& ostr, const Point<T>& p) {
    return ostr << "(" << p.x << ", " << p.y << ")";
}

template <typename T>
struct Line {
    T a, b, c;
    Line(T _a, T _b, T _c) {
        a = _a, b = _b, c = _c;
    }
    Line& fit() {
        // COMMENT OUT THIS PART IF TYPE IS NOT AN INTEGER
        //T gcd = __gcd(a, __gcd(b, c));
        //a /= gcd, b /= gcd, c /= gcd;
        //////////////////////////////////////////////////
        if ((a < 0) || (a == 0 && b < 0)) {
            a = -a, b = -b, c = -c;
        }
        return *this;
    }
    template <typename K>
    K calc(const Point<K>& p) const {
        return a * p.x + b * p.y + c;
    }
    bool operator<(const Line& ot) const {
        return std::tie(a, b, c) < std::tie(ot.a, ot.b, ot.c);
    }
};

template <typename T>
istream& operator>>(istream& istr, Line<T>& l) {
    return istr >> l.a >> l.b >> l.c;
}

template <typename T>
ostream& operator<<(ostream& ostr, const Line<T>& l) {
    return ostr << l.a << " * x + " << l.b << " * y + " << l.c;
}

// line passing through two points
template <typename T>
Line<T> find_line(Point<T> p, Point<T> q) {
    return Line<T>(p.y - q.y, q.x - p.x, p.x * q.y - p.y * q.x).fit();
}

// intersection of lines
template <typename T>
Point<real_t> intersect(Line<T> p, Line<T> q) {
    if (p.a * q.b == p.b * q.a) {
        return {inf, inf};
    }
    else {
        return {real_t(p.b * q.c - q.b * p.c) / real_t(q.b * p.a - q.a * p.b), real_t(q.a * p.c - q.c * p.a) / real_t(q.b * p.a - q.a * p.b)};
    }
}

template <typename T>
struct Segment {
    Point<T> l, r;
    int id;
    bool operator<(const Segment& ot) const {
        if (max(l.x, ot.l.x) <= min(r.x, ot.r.x)) {
            ll x = max(l.x, ot.l.x);
            return l.y * (r.x - l.x) * (ot.r.x - ot.l.x) + (r.y - l.y) * (x - l.x) * (ot.r.x - ot.l.x) < ot.l.y * (ot.r.x - ot.l.x) * (r.x - l.x) + (ot.r.y - ot.l.y) * (x - ot.l.x) * (r.x - l.x);
        }
        else {
            return l.x < ot.l.x;
        }
    }
};

template <typename T>
istream& operator>>(istream& istr, Segment<T>& s) {
    return istr >> s.l >> s.r;
}

template <typename T>
ostream& operator<<(ostream& ostr, const Segment<T>& s) {
    return ostr << "{" << s.l << ", " << s.r << " : " << s.id << "}";
}

const int N = 3e5 + 10;
Segment<ll> a[N];

bool good(int n) {
    if (a[n].l.x == a[n].r.x) {
        return 0;
    }
    if (a[n].l.y == a[n].r.y) {
        return 0;
    }
    for (int i = 1; i <= n - 1; i++) {
        auto p = find_line(Point<ll>{a[i].l.x, a[i].l.y}, Point<ll>{a[i].r.x, a[i].r.y});
        auto q = find_line(Point<ll>{a[n].l.x, a[n].l.y}, Point<ll>{a[n].r.x, a[n].r.y});
        auto cur = intersect(p, q);
        if (cur.x == inf && max(a[i].l.x, a[n].l.x) <= min(a[i].r.x, a[n].r.x)) {
            return 0;
        }
        if (a[i].l.x <= cur.x && cur.x <= a[i].r.x) {
            return 0;
        }
    }
    return 1;
}

void print(int n, int m) {
    cout << n << endl;
    for (int i = 1; i <= n; i++) {
        cout << a[i] << endl;
    }
}

void stress() {
    int C = 1000;
    while (true) {
        int n = rnd() % 10000 + 1;
        bool bad_test = 0;
        for (int i = 1; i <= n && !bad_test; i++) {
            int cnt = 0;
            do {
                cnt++;
                if (cnt > 1000) {
                    bad_test = 1;
                    break;
                }
                a[i].l = {rand() % (C + C + 1) - C, rand() % (C + C + 1) - C};
                a[i].r = {rand() % (C + C + 1) - C, rand() % (C + C + 1) - C};
                a[i].id = i;
                if (a[i].l.x > a[i].r.x) {
                    swap(a[i].l, a[i].r);
                }
            } while (!good(i));
        }
        if (bad_test) {
            continue;
        }
    }
    exit(0);
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
