#include <bits/stdc++.h>

using namespace std;

typedef __int128_t LL;

/*
    Tested on problem: https://codeforces.com/group/I0I2Us0QBe/contest/286100/problem/M
*/

struct Equ {
    LL r, mod;
    Equ(LL _r, LL _mod) : r(_r), mod(_mod) {
    }
};

LL lcm(LL a, LL b) {
    return a / __gcd(a, b) * b;
}

LL gcd(LL a, LL b, LL & x, LL & y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    LL x1, y1;
    LL d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

bool find_any_solution(LL a, LL b, LL c, LL& x0, LL& y0) {
    LL A = a, B = b;
    if (A < 0) A *= -1;
    if (B < 0) B *= -1;
    LL g = gcd(A, B, x0, y0);
    if (c % g != 0) return false;
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 *= -1;
    if (b < 0) y0 *= -1;
    return true;
}

LL CRT_2(Equ p, Equ q) {
    LL x, y;
    if (!find_any_solution(p.mod, -q.mod, q.r - p.r, x, y)) {
        return -1;
    }
    LL X = p.mod * x + p.r;
    LL tot_mod = lcm(p.mod, q.mod);
    X = (X % tot_mod + tot_mod) % tot_mod;
    return X;
}

Equ merge(Equ p, Equ q) {
    return {CRT_2(p, q), lcm(p.mod, q.mod)};
}

LL CRT(const vector<Equ>& vec) {
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
LL a[K];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL_ALIKHAN
    freopen("input.txt", "r", stdin);
#endif

    long long nn, mm;
    int k;
    cin >> nn >> mm >> k;
    LL n = nn, m = mm;
    for (int i = 1; i <= k; i++) {
        long long cur;
        cin >> cur;
        a[i] = cur;
    }
    LL L = 0;
    for (int i = 1; i <= k; i++) {
        if (i == 1) L = a[i];
        else L = lcm(L, a[i]);
        if (L > n) {
            cout << "NO\n";
            return 0;
        }
    }
    vector<Equ> vec;
    for (int i = 1; i <= k; i++) {
        vec.emplace_back(((1 - i) % a[i] + a[i]) % a[i], a[i]);
    }
    LL x = CRT(vec);
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

#ifdef LOCAL_ALIKHAN
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}