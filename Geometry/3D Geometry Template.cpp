#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

ll gcd(ll a, ll b) {
    if (!a || !b) return a + b;
    else return __gcd(a, b);
}

struct Vec {
    ll x, y, z;
    bool is_zero() {
        return x == 0 && y == 0 && z == 0;
    }
    void fit() {
        ll g = gcd(gcd(abs(x), abs(y)), abs(z));
        if (g > 0) {
            x /= g, y /= g, z /= g;
        }
        if ((x < 0) || (x == 0 && y < 0) || (x == 0 && y == 0 && z < 0)) {
            x *= -1, y *= -1, z *= -1;
        }
    }
    Vec operator-(const Vec ot) {
        return {x - ot.x, y - ot.y, z - ot.z};
    }
    Vec operator+(const Vec ot) {
        return {x + ot.x, y + ot.y, z + ot.z};
    }
    void operator-=(const Vec ot) {
        *this = *this - ot;
    }
    void operator+=(const Vec ot) {
        *this = *this + ot;
    }
    Vec operator*(const ll ot) {
        return {x * ot, y * ot, z * ot};
    }
    void operator*=(const ll ot) {
        *this = *this * ot;
    }
    bool operator<(const Vec& ot) const {
        return std::tie(x, y, z) < std::tie(ot.x, ot.y, ot.z);
    }
};

struct Line {
    Vec a, b, B;
    void fit() {
        B = b;
        b -= a;
        b.fit();
    }
};

struct Rat {
    ll p, q;
    void fit() {
        ll g = gcd(abs(p), abs(q));
        if (g > 0) {
            p /= g, q /= g;
        }
        if (q < 0) {
            p *= -1, q *= -1;
        }
    }
    void operator=(const ll& ot) {
        p = ot, q = 1;
    }
    bool operator<(const Rat& ot) const {
        return p * ot.q < q * ot.p;
    }
    bool operator==(const Rat& ot) const {
        return p * ot.q == q * ot.p;
    }
};

struct Point {
    Rat x, y, z;
    void fit() {
        x.fit(), y.fit(), z.fit();
    }
    bool operator<(const Point& ot) const {
        return std::tie(x, y, z) < std::tie(ot.x, ot.y, ot.z);
    }
};

struct Plane {
    Vec norm;
    ll shift;
    bool operator<(const Plane& ot) const {
        return std::tie(norm, shift) < std::tie(ot.norm, ot.shift);
    }
};

ostream& operator <<(ostream& ostr, const Vec& v) {
    return ostr << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

ostream& operator <<(ostream& ostr, const Line& l) {
    return ostr << "f(t) = " << l.a << " + " << l.b << " * t";
}

ostream& operator <<(ostream& ostr, const Rat& ot) {
    return ostr << "(" << ot.p << " / " << ot.q << ")";
}

ostream& operator <<(ostream& ostr, const Point& ot) {
    return ostr << "(" << ot.x << ", " << ot.y << ", " << ot.z << ")";
}

Vec cross(Vec v, Vec u) {
    Vec res;
    res.x = v.y * u.z - v.z * u.y;
    res.y = v.z * u.x - v.x * u.z;
    res.z = v.x * u.y - v.y * u.x;
    return res;
}

ll dot(Vec v, Vec u) {
    return v.x * u.x + v.y * u.y + v.z * u.z;
}

Plane find_plane(Line p, Line q) {
    Plane cur;
    cur.norm = cross(p.b, q.b);
    cur.norm.fit();
    cur.shift = dot(cur.norm, p.a);
    return cur;
}

bool do_inter(Line p, Line q) {
    Plane cur = find_plane(p, q);
    return !(cur.norm.is_zero() || cur.shift != dot(cur.norm, q.a));
}

Point inter(Line p, Line q) {
    Vec r = cross(q.a - p.a, q.B - p.a);
    Vec s = cross(q.a - p.B, q.B - p.B);
    ll k, l;
    if(s.x != 0 || r.x != 0) {
        k = -s.x, l = r.x;
    }
    else if(s.y != 0 || r.y != 0) {
        k = -s.y, l = r.y;
    }
    else {
        k = -s.z, l = r.z;
    }
    Point inter;
    inter.x.p = p.a.x * k + p.B.x * l;
    inter.x.q = k + l;
    inter.y.p = p.a.y * k + p.B.y * l;
    inter.y.q = k + l;
    inter.z.p = p.a.z * k + p.B.z * l;
    inter.z.q = k + l;
    inter.fit();
    return inter;
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
