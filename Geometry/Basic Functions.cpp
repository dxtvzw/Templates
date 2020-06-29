#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

/*
    lol
*/

struct Point {
    ll x, y;
};

struct Line {
    ll a, b, c;
};

bool parallel(Line p, Line q) {
    return p.a * q.b == p.b * q.a;
}

bool cmp_angle(Line p, Line q) {
    return p.a * q.b < p.b * q.a;
}

Line find_line(Point p, Point q) {
    ll a = p.y - q.y;
    ll b = q.x - p.x;
    ll c = p.x * q.y - p.y * q.x;
    ll gcd = __gcd(a, __gcd(b, c));
    if (a / gcd < 0) {
        gcd *= -1;
    }
    return {a / gcd, b / gcd, c / gcd};
}

////////////////////////////////////// Segment Intersection in 2D //////////////////////////////////////
bool onSegment(Point p, Point q, Point r) {
    return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
}

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0)? 1: 2;
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    if (o1 != o2 && o3 != o4) return 1;
    if (o1 == 0 && onSegment(p1, p2, q1)) return 1;
    if (o2 == 0 && onSegment(p1, q2, q1)) return 1;
    if (o3 == 0 && onSegment(p2, p1, q2)) return 1;
    if (o4 == 0 && onSegment(p2, q1, q2)) return 1;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

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
