#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

typedef double Type;

struct Point {
    Type x, y;
};

struct Line {
    Type a, b, c;
};

Type dist(Point p, Point q) {
    return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}

Type dot(Point O, Point p, Point q) {
    return (p.x - O.x) * (q.x - O.x) + (p.y - O.y) * (q.y - O.y);
}

Type cross(Point p, Point q) {
    return p.x * q.y - p.y * q.x;
}

Type cross(Point O, Point p, Point q) {
    return cross({p.x - O.x, p.y - O.y}, {q.x - O.x, q.y - O.y});
}

Type angle(Point O, Point p, Point q) {
    return acos(dot(O, p, q) / (dist(O, p) * dist(O, q)));
}

bool parallel(Line p, Line q) {
    return p.a * q.b == p.b * q.a;
}

bool cmp_angle(Line p, Line q) {
    return p.a * q.b < p.b * q.a;
}

Line find_line(Point p, Point q) {
    Type a = p.y - q.y;
    Type b = q.x - p.x;
    Type c = p.x * q.y - p.y * q.x;
    /*
    // if Type == int or long long
    Type gcd = __gcd(a, __gcd(b, c));
    if (a / gcd < 0) {
        gcd *= -1;
    }
    return {a / gcd, b / gcd, c / gcd};
    */
    return {a, b, c};
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
