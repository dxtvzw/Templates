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

struct Point {
    int x, y;
    bool operator==(const Point& ot) const {
        return x == ot.x && y == ot.y;
    }
    bool operator!=(const Point& ot) const {
        return x != ot.x || y != ot.y;
    }
    bool operator<(const Point& ot) const {
        return (x < ot.x) || (x == ot.x && y < ot.y);
    }
};

struct Rect {
    Point ld, ru, lu, rd;
    void calc() {
        lu = {ld.x, ru.y};
        rd = {ru.x, ld.y};
    }
    bool operator==(const Rect& ot) const {
        return ld == ot.ld && ru == ot.ru;
    }
};

struct Seg {
    Point l, r;
};

const int inf = 1e9 + 10;
const Point p_zero = {inf, inf};
const Rect r_zero = {{0, 0}, {-1, -1}};

bool is_inside(Point p, Rect a) {
    return a.ld.x <= p.x && p.x <= a.ru.x && a.ld.y <= p.y && p.y <= a.ru.y;
}

Point seg_inter(Seg a, Seg b) {
    if (a.l.x == a.r.x) {
        swap(a, b);
    }
    if (b.l.x < a.l.x || a.r.x < b.l.x || a.l.y < b.l.y || b.r.y < a.l.y) {
        return p_zero;
    }
    else {
        return {b.l.x, a.l.y};
    }
}

Rect rect_inter(Rect a, Rect b) {
    if (a.ru.x < b.ld.x || b.ru.x < a.ld.x || a.ru.y < b.ld.y || b.ru.y < a.ld.y) {
        return r_zero;
    }
    vector<Point> all = {a.ld, a.lu, a.rd, a.ru, b.ld, b.lu, b.rd, b.ru};
    Seg A[4] = {{a.ld, a.lu}, {a.ld, a.rd}, {a.rd, a.ru}, {a.lu, a.ru}};
    Seg B[4] = {{b.ld, b.lu}, {b.ld, b.rd}, {b.rd, b.ru}, {b.lu, b.ru}};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if ((i - j) % 2 != 0) {
                all.pb(seg_inter(A[i], B[j]));
            }
        }
    }
    set<Point> good;
    for (Point p : all) {
        if (p != p_zero && is_inside(p, a) && is_inside(p, b)) {
            good.insert(p);
        }
    }
    Rect ans = {*good.begin(), *good.rbegin()};
    ans.calc();
    return ans;
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
