#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128_t LL;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

typedef vector<int> poly;

ostream& operator<<(ostream& ostr, const poly& p) {
    for (int i = 0; i < p.size(); i++) {
        ostr << p[i] << " * x^" << i;
        if (i + 1 != p.size()) {
            ostr << " + ";
        }
    }
    return ostr;
}

void fix(poly& p) {
    while (!p.empty() && p.back() == 0) p.pop_back();
    if (p.empty()) p.pb(0);
}

poly add(const poly& p, const poly& q) {
    poly res(max(p.size(), q.size()), 0);
    for (int i = 0; i < res.size(); i++) {
        if (i < p.size()) res[i] += p[i];
        if (i < q.size()) res[i] += q[i];
    }
    fix(res);
    return res;
}

poly mult(const poly& p, const poly& q) {
    poly res(p.size() + q.size() - 1, 0);
    for (int i = 0; i < p.size(); i++) {
        for (int j = 0; j < q.size(); j++) {
            res[i + j] += p[i] * q[j];
        }
    }
    fix(res);
    return res;
}

poly get_poly(int mask, int n) {
    poly p(n);
    for (int i = 0; i < n + n; i += 2) {
        p[i / 2] = ((mask >> i) & 3);
    }
    fix(p);
    return p;
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
