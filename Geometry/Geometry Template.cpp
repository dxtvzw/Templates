#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

typedef long long Type_1;
typedef double Type_2;

const Type_2 pi = acos(-1);

struct Point {
    Type_1 x, y;
    bool operator<(const Point& q) const {
        return x < q.x || (x == q.x && y < q.y);
    }
    bool operator==(const Point& q) const {
        return x == q.x && y == q.y;
    }
    bool operator!=(const Point& q) const {
        return x != q.x || y != q.y;
    }
};

ostream& operator<<(ostream& ostr, const Point& p) {
	return ostr << p.x << " " << p.y;
}

struct Line {
    Type_1 a, b, c;
};

ostream& operator<<(ostream& ostr, const Line& l) {
	return ostr << l.a << " * x + " << l.b << " * y + " << l.c << "\n";
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
    return cross({p.x - O.x, p.y - O.y}, {q.x - O.x, q.y - O.y});
}

Type_2 dist(Point p, Point q) {
    return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}

Type_2 angle(Point O, Point p, Point q) {
    return acos(Type_2(dot(O, p, q)) / Type_2(dist(O, p) * dist(O, q)));
}

bool parallel(Line p, Line q) {
    return p.a * q.b == p.b * q.a;
}

bool cmp_angle(Line p, Line q) {
    return p.a * q.b < p.b * q.a;
}

Line find_line(Point p, Point q) {
    Type_1 a = p.y - q.y;
    Type_1 b = q.x - p.x;
    Type_1 c = p.x * q.y - p.y * q.x;
    /*
    // if Type_1 == int or long long
    Type gcd = __gcd(a, __gcd(b, c));
    if (a / gcd < 0) {
        gcd *= -1;
    }
    return {a / gcd, b / gcd, c / gcd};
    */
    return {a, b, c};
}

Type_2 area(Point A, Point B, Point C) {
    Type_2 a = dist(B, C), b = dist(A, C), c = dist(A, B);
    Type_2 p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

Type_2 radius(Point A, Point B, Point C) {
    return dist(A, B) * dist(B, C) * dist(C, A) / (area(A, B, C) * 4);
}

vector<Point> convex_hull(vector<Point> v) {
    int n = v.size(), k = 0;
    if (n < 3) return {};
    vector<Point> hull(2*n);
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(hull[k-2], hull[k-1], v[i]) <= 0) k--;
        hull[k++] = v[i];
    }
    for (int i = n - 1, t = k + 1; i > 0; i--) {
        while (k >= t && cross(hull[k-2], hull[k-1], v[i-1]) <= 0) k--;
        hull[k++] = v[i-1];
    }
    hull.resize(k-1);
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