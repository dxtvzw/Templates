#include <bits/stdc++.h>
using namespace std;
typedef __int128_t ll;
typedef long long LL;
typedef long double ld;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

/*
    Tested on problem: https://codeforces.com/group/I0I2Us0QBe/contest/286100/problem/M
*/

struct Equ {
    ll r, mod;
};

ll __lcm(ll a, ll b) {
    return a / __gcd(a, b) * b;
}

ll gcd(ll a, ll b, ll & x, ll & y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	ll x1, y1;
	ll d = gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

bool find_any_solution(ll a, ll b, ll c, ll& x0, ll& y0) {
    ll A = a, B = b;
    if (A < 0) A *= -1;
    if (B < 0) B *= -1;
	ll g = gcd(A, B, x0, y0);
	if (c % g != 0) return 0;
	x0 *= c / g;
	y0 *= c / g;
	if (a < 0) x0 *= -1;
	if (b < 0) y0 *= -1;
	return 1;
}

ll CRT_2(Equ p, Equ q) {
    ll x, y;
    if (!find_any_solution(p.mod, -q.mod, q.r - p.r, x, y)) {
        return -1;
    }
    ll X = p.mod * x + p.r;
    ll tot_mod = __lcm(p.mod, q.mod);
    X = (X % tot_mod + tot_mod) % tot_mod;
    return X;
}

Equ merge(Equ p, Equ q) {
    return {CRT_2(p, q), __lcm(p.mod, q.mod)};
}

ll CRT(vector<Equ> vec) {
    Equ cur = vec[0];
    for (int i = 1; i < vec.size(); i++) {
        cur = merge(cur, vec[i]);
        if (cur.r == -1) {
            return -1;
        }
    }
    return cur.r;
}

const int K = 1e4 + 10;
ll a[K];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    long long nn, mm;
    int k;
    cin >> nn >> mm >> k;
    ll n = nn, m = mm;
    for (int i = 1; i <= k; i++) {
        long long cur;
        cin >> cur;
        a[i] = cur;
    }
    ll L = 0;
    for (int i = 1; i <= k; i++) {
        if (i == 1) L = a[i];
        else L = __lcm(L, a[i]);
        if (L > n) {
            cout << "NO\n";
            return 0;
        }
    }
    vector<Equ> vec;
    for (int i = 1; i <= k; i++) {
        vec.pb({((1 - i) % a[i] + a[i]) % a[i], a[i]});
    }
    ll x = CRT(vec);
    if (x == 0) x = L;
    if (x == -1 || x + k - 1 > m) {
        cout << "NO\n";
        return 0;
    }
    for (int i = 1; i <= k; i++) {
        if (a[i] != __gcd(L, x + i - 1)) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";

#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
