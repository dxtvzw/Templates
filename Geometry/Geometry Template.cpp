#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//typedef __int128_t LL;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

typedef long long Type_1;
typedef double Type_2;

const Type_2 pi = acos(-1);

struct Point {
    Type_1 x, y;
    void fit() {
        x *= 2, y *= 2;
    }
    Point operator+(const Point& ot) {
        return {x + ot.x, y + ot.y};
    }
    bool operator<(const Point& ot) const {
        return std::tie(x, y) < std::tie(ot.x, ot.y);
    }
};

istream& operator>>(istream& istr, Point& p) {
    return istr >> p.x >> p.y;
}

ostream& operator<<(ostream& ostr, const Point& p) {
    return ostr << p.x << " " << p.y;
}

struct Line {
    Type_1 a, b, c;
    void fit() {
        Type_1 gcd = __gcd(a, __gcd(b, c));
        a /= gcd, b /= gcd, c /= gcd;
        if ((a < 0) || (a == 0 && b < 0)) {
            a *= -1, b *= -1, c *= -1;
        }
    }
    bool operator<(const Line& ot) const {
        return std::tie(a, b, c) < std::tie(ot.a, ot.b, ot.c);
    }
};

ostream& operator<<(ostream& ostr, const Line& l) {
    return ostr << l.a << " * x + " << l.b << " * y + " << l.c;
}

Type_1 dot(Point p, Point q) {
    return p.x * q.x + p.y * q.y;
}

Type_1 dot(Point O, Point p, Point q) {
    return (p.x - O.x) * (q.x - O.x) + (p.y - O.y) * (q.y - O.y);
}

Type_1 cross(Point p, Point q) {
    return p.x * q.y - p.y * q.x;
}

Type_1 cross(Point O, Point p, Point q) {
    return (p.x - O.x) * (q.y - O.y) - (p.y - O.y) * (q.x - O.x);
}

Type_1 dist2(Point p, Point q) {
    return (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y);
}

Type_2 dist(Point p, Point q) {
    return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}

Type_2 angle(Point O, Point p, Point q) {
    return acos(Type_2(dot(O, p, q)) / Type_2(dist(O, p) * dist(O, q)));
}

Line find_line(Point p, Point q) {
    Type_1 a = p.y - q.y;
    Type_1 b = q.x - p.x;
    Type_1 c = p.x * q.y - p.y * q.x;
    Line l = {a, b, c};
    l.fit();
    return l;
}

Line mid_perp(Point p, Point q) {
    Line l = {2 * (p.x - q.x), 2 * (p.y - q.y), -((p.x - q.x) * (p.x + q.x) + (p.y - q.y) * (p.y + q.y))};
    l.fit();
    return l;
}

Type_2 area(Point A, Point B, Point C) {
    Type_2 a = dist(B, C), b = dist(A, C), c = dist(A, B);
    Type_2 p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
    // return cross(A, B, C) / 2;
}

Type_2 radius(Point A, Point B, Point C) {
    return dist(A, B) * dist(B, C) * dist(C, A) / (area(A, B, C) * 4);
}

vector<Point> convex_hull(vector<Point> v) {
    int n = v.size(), k = 0;
    if (n < 3) return {};
    vector<Point> hull(2 * n);
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
