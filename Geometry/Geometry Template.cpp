#include <bits/stdc++.h>
using namespace std;
//typedef long long ll;
typedef __int128_t ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

typedef long double TP;

template <typename T>
struct Point {
    T x, y;
    void fit() {
        x *= 2, y *= 2;
    }
    bool operator<(const Point& ot) const {
        return std::tie(x, y) < std::tie(ot.x, ot.y);
    }
};

#define nan my_nan

const TP nan = 3e18 + 123123;
const Point<TP> nap = {nan, nan};

template <typename T>
istream& operator>>(istream& istr, Point<T>& p) {
    return istr >> p.x >> p.y;
}

template <typename T>
ostream& operator<<(ostream& ostr, const Point<T>& p) {
    return ostr << p.x << " " << p.y;
    //return ostr << "(" << p.x << ", " << p.y << ")";
}

template <typename T>
struct Line {
    T a, b, c;
    void fit() {
        /*
        T gcd = __gcd(a, __gcd(b, c));
        a /= gcd, b /= gcd, c /= gcd;
        */
        if ((a < 0) || (a == 0 && b < 0)) {
            a *= -1, b *= -1, c *= -1;
        }
    }
    bool operator<(const Line& ot) const {
        return std::tie(a, b, c) < std::tie(ot.a, ot.b, ot.c);
    }
};

template <typename T>
ostream& operator<<(ostream& ostr, const Line<T>& l) {
    return ostr << l.a << " * x + " << l.b << " * y + " << l.c;
}

template <typename T>
struct Circle {
    Point<T> o;
    T r;
    void fit() {
        o.fit();
        r *= 2;
    }
};

template <typename T>
istream& operator>>(istream& istr, Circle<T>& w) {
    return istr >> w.o >> w.r;
}

template <typename T>
ostream& operator<<(ostream& ostr, const Circle<T>& w) {
    return ostr << w.o << " : " << w.r;
}

// solve a * x^2 + b * x + c = 0
pair<TP, TP> solve_quad(TP a, TP b, TP c) {
    ld d = b * b - 4 * a * c;
    if (d < 0) {
        return {my_nan, my_nan};
    }
    else {
        return {(-b + sqrt(d)) / (2 * a), (-b - sqrt(d)) / (2 * a)};
    }
}

template <typename T1, typename T2>
pair<Point<TP>, Point<TP>> intersect(Line<T1> l, Circle<T2> w) {
    ld a = l.a, b = l.b, c = l.c, p = w.o.x, q = w.o.y, r = w.r;
    if (b != 0) {
        auto x = solve_quad(a * a / b / b + 1, 2 * a / b * (c / b + q) - 2 * p, p * p + (c / b + q) * (c / b + q) - r * r);
        if (x.F == nan) {
            return {nap, nap};
        }
        else {
            return {{x.F, -a / b * x.F - c / b}, {x.S, -a / b * x.S - c / b}};
        }
    }
    else {
        swap(l.a, l.b);
        swap(w.o.x, w.o.y);
        auto ans = intersect(l, w);
        swap(ans.F.x, ans.F.y);
        swap(ans.S.x, ans.S.y);
        return ans;
    }
}

template <typename T>
T dot(Point<T> p, Point<T> q) {
    return p.x * q.x + p.y * q.y;
}

template <typename T>
T dot(Point<T> O, Point<T> p, Point<T> q) {
    return (p.x - O.x) * (q.x - O.x) + (p.y - O.y) * (q.y - O.y);
}

template <typename T>
T cross(Point<T> p, Point<T> q) {
    return p.x * q.y - p.y * q.x;
}

template <typename T>
T cross(Point<T> O, Point<T> p, Point<T> q) {
    return (p.x - O.x) * (q.y - O.y) - (p.y - O.y) * (q.x - O.x);
}

template <typename T>
T dist2(Point<T> p, Point<T> q) {
    return (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y);
}

template <typename T1, typename T2>
TP dist(Point<T1> p, Point<T2> q) {
    return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}

template <typename T1, typename T2, typename T3>
TP angle(Point<T1> O, Point<T2> p, Point<T3> q) {
    return acos(Type_2(dot(O, p, q)) / Type_2(dist(O, p) * dist(O, q)));
}

template <typename T>
Line<T> find_line(Point<T> p, Point<T> q) {
    T a = p.y - q.y;
    T b = q.x - p.x;
    T c = p.x * q.y - p.y * q.x;
    Line l = {a, b, c};
    l.fit();
    return l;
}

template <typename T>
Line<T> mid_perp(Point<T> p, Point<T> q) {
    Line<T> l = {2 * (p.x - q.x), 2 * (p.y - q.y), -((p.x - q.x) * (p.x + q.x) + (p.y - q.y) * (p.y + q.y))};
    l.fit();
    return l;
}

template <typename T>
TP area(Point<T> A, Point<T> B, Point<T> C) {
    TP a = dist(B, C), b = dist(A, C), c = dist(A, B);
    TP p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
    // return cross(A, B, C) / 2;
}

template <typename T>
TP radius(Point<T> A, Point<T> B, Point<T> C) {
    return dist(A, B) * dist(B, C) * dist(C, A) / (area(A, B, C) * 4);
}

template <typename T>
vector<Point<T>> convex_hull(vector<Point<T>> v) {
    int n = v.size(), k = 0;
    if (n < 3) return v;
    vector<Point<T>> hull(2 * n);
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(hull[k - 2], hull[k - 1], v[i]) <= 0) k--;
        hull[k++] = v[i];
    }
    for (int i = n - 1, t = k + 1; i > 0; i--) {
        while (k >= t && cross(hull[k - 2], hull[k - 1], v[i - 1]) <= 0) k--;
        hull[k++] = v[i - 1];
    }
    hull.resize(k - 1);
    return hull;
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
