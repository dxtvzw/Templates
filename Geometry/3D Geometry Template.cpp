#include <bits/stdc++.h>

using namespace std;

typedef long long val_t;

val_t gcd(val_t a, val_t b) {
    return !a || !b ? abs(a + b) : __gcd(a, b);
}

struct Vec {
    val_t x = 0, y = 0, z = 0;
    [[nodiscard]] bool is_zero() const {
        return x == 0 && y == 0 && z == 0;
    }
    void fit() {
        val_t g = gcd(gcd(abs(x), abs(y)), abs(z));
        if (g > 0) {
            x /= g, y /= g, z /= g;
        }
        if ((x < 0) || (x == 0 && y < 0) || (x == 0 && y == 0 && z < 0)) {
            x *= -1, y *= -1, z *= -1;
        }
    }
    Vec operator-(const Vec ot) const {
        return {x - ot.x, y - ot.y, z - ot.z};
    }
    Vec operator+(const Vec ot) const {
        return {x + ot.x, y + ot.y, z + ot.z};
    }
    Vec& operator-=(const Vec ot) {
        return *this = *this - ot;
    }
    Vec& operator+=(const Vec ot) {
        return *this = *this + ot;
    }
    Vec operator*(const val_t ot) const {
        return {x * ot, y * ot, z * ot};
    }
    Vec& operator*=(const val_t ot) {
        return *this = *this * ot;
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
    val_t p = 0, q = 1;
    void fit() {
        val_t g = gcd(abs(p), abs(q));
        if (g > 0) {
            p /= g, q /= g;
        }
        if (q < 0) {
            p *= -1, q *= -1;
        }
    }
    Rat& operator=(val_t ot) {
        p = ot, q = 1;
        return *this;
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
    val_t shift = 0;
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
    return {
            v.y * u.z - v.z * u.y,
            v.z * u.x - v.x * u.z,
            v.x * u.y - v.y * u.x
    };
}

val_t dot(Vec v, Vec u) {
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
    val_t k, l;
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