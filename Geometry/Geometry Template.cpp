#include <bits/stdc++.h>

using namespace std;

std::mt19937 rnd;

#define nan my_nan

typedef long double real_t;
const real_t eps = 1e-9;
const real_t inf = 1e18 + 10;
const real_t nan = inf + inf + 123123;
const real_t pi = acos(-1);
const long long mult_const = 2;

real_t rand_real(real_t l, real_t r) {
    std::uniform_real_distribution<real_t> distribution(l, r);
    return distribution(rnd);
}

bool are_eq(real_t a, real_t b) {
    return abs(a - b) < eps;
}

template<typename T>
struct Point {
    T x, y;
    int id;

    Point &fit() {
        x *= mult_const;
        y *= mult_const;
        return *this;
    }

    Point operator+(const Point &ot) const {
        return {x + ot.x, y + ot.y};
    }

    Point operator-(const Point &ot) const {
        return {x - ot.x, y - ot.y};
    }

    Point operator*(T val) const {
        return {x * val, y * val};
    }

    Point operator/(T val) const {
        return {x / val, y / val};
    }

    Point operator*(const Point &ot) const {
        return {x * ot.x - y * ot.y, x * ot.y + y * ot.x};
    }

    Point &operator+=(const Point &ot) {
        return *this = *this + ot;
    }

    Point &operator-=(const Point &ot) {
        return *this = *this - ot;
    }

    Point &operator*=(T val) {
        return *this = *this * val;
    }

    Point &operator/=(T val) {
        return *this = *this / val;
    }

    Point &operator*=(const Point &ot) {
        return *this = *this * ot;
    }

    bool operator<(const Point &ot) const {
        return std::tie(x, y) < std::tie(ot.x, ot.y);
    }

    bool operator>(const Point &ot) const {
        return std::tie(x, y) > std::tie(ot.x, ot.y);
    }

    bool operator==(const Point &ot) const {
        if constexpr (std::is_integral_v<T>) {
            return x == ot.x && y == ot.y;
        } else {
            return are_eq(x, ot.x) && are_eq(y, ot.y);
        }
    }

    bool operator!=(const Point &ot) const {
        return !(*this == ot);
    }
};

typedef pair<Point<real_t>, Point<real_t>> ppp;
const Point<real_t> nap = {nan, nan};

template<typename T>
istream &operator>>(istream &istr, Point<T> &p) {
    return istr >> p.x >> p.y;
}

template<typename T>
ostream &operator<<(ostream &ostr, const Point<T> &p) {
    return ostr << "(" << p.x << ", " << p.y << ")";
}

template<typename T>
struct Line {
    T a, b, c;

    Line(T _a, T _b, T _c) {
        a = _a, b = _b, c = _c;
    }

    Line &fit() {
        if constexpr (std::is_integral_v<T>) {
            T gcd = __gcd(a, __gcd(b, c));
            a /= gcd, b /= gcd, c /= gcd;
        }
        if ((a < 0) || (a == 0 && b < 0)) {
            a = -a, b = -b, c = -c;
        }
        return *this;
    }

    template<typename K>
    K calc(const Point<K> &p) const {
        return a * p.x + b * p.y + c;
    }

    bool operator<(const Line &ot) const {
        return std::tie(a, b, c) < std::tie(ot.a, ot.b, ot.c);
    }
};

template<typename T>
istream &operator>>(istream &istr, Line<T> &l) {
    return istr >> l.a >> l.b >> l.c;
}

template<typename T>
ostream &operator<<(ostream &ostr, const Line<T> &l) {
    return ostr << l.a << " * x + " << l.b << " * y + " << l.c;
}

template<typename T>
struct Circle {
    Point<T> o;
    T r;

    Circle &fit() {
        o.fit();
        r *= mult_const;
        return *this;
    }

    bool operator==(const Circle &ot) const {
        return o == ot.o && r == ot.r;
    }
};

template<typename T>
istream &operator>>(istream &istr, Circle<T> &w) {
    return istr >> w.o >> w.r;
}

template<typename T>
ostream &operator<<(ostream &ostr, const Circle<T> &w) {
    return ostr << "(" << w.o << " : " << w.r << ")";
}

// intersection of lines
template<typename T>
Point<real_t> intersect(Line<T> p, Line<T> q) {
    if (p.a * q.b == p.b * q.a) {
        return nap;
    } else {
        return {real_t(p.b * q.c - q.b * p.c) / real_t(q.b * p.a - q.a * p.b),
                real_t(q.a * p.c - q.c * p.a) / real_t(q.b * p.a - q.a * p.b)};
    }
}

/*
        ================================ THIS MIGHT NOT WORK BEGIN ===================================
*/

// solving quadratic equation
pair<real_t, real_t> solve_quad(real_t a, real_t b, real_t c) {
    real_t d = b * b - 4 * a * c;
    if (d < 0) {
        return {my_nan, my_nan};
    } else {
        return {(-b + sqrt(d)) / (2 * a), (-b - sqrt(d)) / (2 * a)};
    }
}

// intersection of line and circle
template<typename T1, typename T2>
ppp intersect(Line<T1> l, Circle<T2> w) {
    real_t a = l.a, b = l.b, c = l.c, p = w.o.x, q = w.o.y, r = w.r;
    assert(!are_eq(a, 0) || !are_eq(b, 0)); ////////////////////////////////////////// BE CAREFUL WITH THIS ASSERT
    if (abs(b) > eps) {
        auto x = solve_quad(a * a / b / b + 1, 2 * a / b * (c / b + q) - 2 * p,
                            p * p + (c / b + q) * (c / b + q) - r * r);
        if (abs(x.first - nan) <= eps) {
            return {nap, nap};
        } else {
            return {{x.first, -a / b * x.first - c / b},
                    {x.second, -a / b * x.second - c / b}};
        }
    } else {
        swap(l.a, l.b);
        swap(w.o.x, w.o.y);
        auto ans = intersect(l, w);
        swap(ans.first.x, ans.first.y);
        swap(ans.second.x, ans.second.y);
        return ans;
    }
}

/*
        ================================ THIS MIGHT NOT WORK END ===================================
*/

// invert point with respect to circle
template<typename T>
Point<T> invert(Point<T> p, Circle<T> w) {
    p -= w.o;
    p *= w.r * w.r / (p.x * p.x + p.y * p.y);
    p += w.o;
    return p;
}

template<typename T>
T dot(Point<T> p, Point<T> q) {
    return p.x * q.x + p.y * q.y;
}

template<typename T>
T dot(Point<T> O, Point<T> p, Point<T> q) {
    return (p.x - O.x) * (q.x - O.x) + (p.y - O.y) * (q.y - O.y);
}

template<typename T>
T cross(Point<T> p, Point<T> q) {
    return p.x * q.y - p.y * q.x;
}

template<typename T>
T cross(Point<T> O, Point<T> p, Point<T> q) {
    return (p.x - O.x) * (q.y - O.y) - (p.y - O.y) * (q.x - O.x);
}

// square of distance between two points
template<typename T>
T dist2(Point<T> p, Point<T> q) {
    return (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y);
}

// distance between two points
template<typename T>
real_t dist(Point<T> p, Point<T> q) {
    return sqrt(real_t((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y)));
}

// angle p O q
template<typename T>
real_t angle(Point<T> O, Point<T> p, Point<T> q) {
    return acos(real_t(dot(O, p, q)) / dist(O, p) / dist(O, q));
}

// angle opposite to the side 'c'
real_t angle(real_t a, real_t b, real_t c) {
    assert(a + b > c && b + c > a && c + a > b);
    return acos((a * a + b * b - c * c) / (2 * a * b));
}

// line passing through two points
template<typename T>
Line<T> find_line(Point<T> p, Point<T> q) {
    return Line<T>(p.y - q.y, q.x - p.x, p.x * q.y - p.y * q.x).fit();
}

// perpendicular bisector
template<typename T>
Line<T> perp_bis(Point<T> p, Point<T> q) {
    return Line<T>(2 * (p.x - q.x), 2 * (p.y - q.y), -((p.x - q.x) * (p.x + q.x) + (p.y - q.y) * (p.y + q.y))).fit();
}

/*
    =============================== THIS AREA IS ALWAYS NON-NEGATIVE =================================================
*/
// area of polygon
template<typename T>
real_t area(const vector<Point<T>> &v) {
    real_t ans = cross(v.back(), v.front());
    for (int i = 0; i + 1 < v.size(); i++) {
        ans += cross(v[i], v[i + 1]);
    }
    return abs(ans) / 2;
}

// area of triangle
template<typename T>
real_t area(Point<T> A, Point<T> B, Point<T> C) {
    return abs(real_t(cross(A, B, C))) / 2;
}

/*
    ==================================================================================================================
*/

// radius of circumscribed circle
template<typename T>
real_t radius(Point<T> A, Point<T> B, Point<T> C) {
    return dist(A, B) * dist(B, C) * dist(C, A) / (area(A, B, C) * 4);
}

// convex hull of points
template<typename T>
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

// divides segment in given ration AC = k, BC = 1 - k
Point<real_t> div_seg(Point<real_t> a, Point<real_t> b, real_t k) {
    return a * (1 - k) + b * k;
}

#define rotate my_complex_rotation

// rotation of point A by alpha degrees (in radians) counterclockwise centered at point O
Point<real_t> rotate(Point<real_t> O, Point<real_t> A, real_t alpha) {
    A -= O;
    A *= Point<real_t>{cos(alpha), sin(alpha)};
    A += O;
    return A;
}

// closest between two points to the given one
Point<real_t> get_closest(ppp p, Point<real_t> a) {
    if (dist2(p.first, a) < dist2(p.second, a)) {
        return p.first;
    } else {
        return p.second;
    }
}

// closest between two points to the given two
Point<real_t> get_closest(ppp p, Point<real_t> a, Point<real_t> b) {
    if (dist(p.first, a) + dist(p.first, b) < dist(p.second, a) + dist(p.second, b)) {
        return p.first;
    } else {
        return p.second;
    }
}

// points of tangency from point to circle
ppp get_tangents(Point<real_t> a, Circle<real_t> w) {
    if (abs(dist(a, w.o) - w.r) < eps) {
        return {a, a};
    }
    real_t alpha = acos(w.r / dist(a, w.o));
    auto p = intersect(find_line(rotate(w.o, a, alpha), w.o), w);
    auto q = intersect(find_line(rotate(w.o, a, -alpha), w.o), w);
    return {get_closest(p, a, a), get_closest(q, a, a)};
    /*
    real_t d = dist(a, w.o);
    real_t ah = d - w.r * w.r / d;
    Point<real_t> h = div_seg(a, w.o, ah / d);
    return intersect(perp_bis(a, h * 2 - a), w);
    */
}

// check if C lies on segment between a and b
template<typename T>
bool on_seg(Point<T> a, Point<T> b, Point<T> c) {
    Line l = find_line(a, b);
    return min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x) && min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y) &&
           l.a * c.x + l.b * c.y + l.c == 0;
}

/*
        ====================== NOT TESTED BEGIN ======================
*/

// calculate angle in a triangle (a, b, c) between a and b
real_t get_angle(real_t a, real_t b, real_t c) {
    return acos((a * a + b * b - c * c) / (2 * a * b));
}

template<typename T>
real_t area_of_circle(Circle<T> a) {
    return pi * a.r * a.r;
}

template<typename T>
real_t area_of_circle_segment(Circle<T> a, real_t alpha) {
    return alpha / 2 * a.r * a.r - sin(alpha) / 2 * a.r * a.r;
}

template<typename T>
real_t area_of_circle_intersection(Circle<T> a, Circle<T> b) {
    real_t d = dist(a.o, b.o);
    if (d >= a.r + b.r) {
        return 0;
    } else if (d <= abs(a.r - b.r)) {
        return min(area_of_circle(a), area_of_circle(b));
    }
    return area_of_circle_segment(a, 2 * get_angle(a.r, d, b.r)) +
           area_of_circle_segment(b, 2 * get_angle(b.r, d, a.r));
}

template<typename T>
real_t area_of_circle_union(Circle<T> a, Circle<T> b) {
    return area_of_circle(a) + area_of_circle(b) - area_of_circle_intersection(a, b);
}

template<typename T>
real_t area_of_circle_difference(Circle<T> a, Circle<T> b) {
    return area_of_circle(a) - area_of_circle_intersection(a, b);
}

// area of intersection of semicircle a pointing down and circle b
template<typename T>
real_t area_of_semicirlce_circle_intersection(Circle<T> a, Circle<T> b) {
    return 0;
}

/*
        ====================== NOT TESTED END ======================
*/

// flag = 0 - no common points, -1 - same circles, 1 - circles touch, 2 - circles intersect
struct CircleIntersection {
    int flag;
    Point<real_t> a, b;

    CircleIntersection(int _flag) {
        flag = _flag;
    }

    CircleIntersection(int _flag, Point<real_t> _a) {
        flag = _flag;
        a = _a;
    }

    CircleIntersection(int _flag, Point<real_t> _a, Point<real_t> _b) {
        flag = _flag;
        a = min(_a, _b);
        b = max(_a, _b);
    }
};

ostream &operator<<(ostream &ostr, CircleIntersection x) {
    if (x.flag == 0 || x.flag == -1) {
        return ostr << x.flag;
    } else if (x.flag == 1) {
        return ostr << x.flag << "\n" << x.a;
    } else {
        return ostr << x.flag << "\n" << x.a << "\n" << x.b;
    }
}

// get closest point from cur to the circle a
template<typename T>
Point<real_t> get_on_circle(ppp cur, Circle<T> a) {
    return abs(dist2(cur.first, a.o) - a.r * a.r) < abs(dist2(cur.second, a.o) - a.r * a.r) ? cur.first : cur.second;
}

// intersection of two circles
// tested on: https://official.contest.yandex.ru/contest/28976/problems/I/
template<typename T>
CircleIntersection intersect(Circle<T> A, Circle<T> B) {
    Circle<real_t> a = {{A.o.x, A.o.y}, A.r};
    Circle<real_t> b = {{B.o.x, B.o.y}, B.r};
    T d2 = dist2(a.o, b.o);
    real_t d = dist(a.o, b.o);
    if (A.r < B.r) {
        swap(a, b);
        swap(A, B);
    }
    if (A.o == B.o) {
        if (A.r == B.r) {
            return {-1};
        } else {
            return {0};
        }
    } else if (d2 >= A.r * A.r) {
        if (d2 > (A.r + B.r) * (A.r + B.r)) {
            return {0};
        } else if (d2 == (A.r + B.r) * (A.r + B.r)) {
            auto cur = intersect(find_line(a.o, b.o), a);
            return {1, get_on_circle(cur, b)};
        } else {
            real_t alpha = get_angle(a.r, d, b.r);
            Point<real_t> p = a.o + (b.o - a.o) / d * a.r;
            return {2, rotate(a.o, p, alpha), rotate(a.o, p, -alpha)};
        }
    } else {
        if (d2 < (A.r - B.r) * (A.r - B.r)) {
            return {0};
        } else if (d2 == (A.r - B.r) * (A.r - B.r)) {
            auto cur = intersect(find_line(a.o, b.o), a);
            return {1, get_on_circle(cur, b)};
        } else {
            real_t alpha = get_angle(a.r, d, b.r);
            Point<real_t> p = a.o + (b.o - a.o) / d * a.r;
            return {2, rotate(a.o, p, alpha), rotate(a.o, p, -alpha)};
        }
    }
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