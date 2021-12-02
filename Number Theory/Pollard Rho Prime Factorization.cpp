#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef __int128_t LL;

ll mult(ll a, ll b, ll M) {
    ll ret = LL(1) * a * b - M * ll(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= (ll)M);
}

ll binpow(ll b, ll e, ll mod) {
    ll ans = 1;
    for (; e; b = mult(b, b, mod), e /= 2)
        if (e & 1) ans = mult(ans, b, mod);
    return ans;
}

bool is_prime(ll n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ll A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
            s = __builtin_ctzll(n-1), d = n >> s;
    for (ll a : A) {   // ^ count trailing zeroes
        ll p = binpow(a%n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = mult(p, p, n);
        if (p != n-1 && i != s) return false;
    }
    return true;
}

ll pollard(ll n) {
    auto f = [n](ll x) { return mult(x, x, n) + 1; };
    ll x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    while (t++ % 40 || __gcd(prd, n) == 1) {
        if (x == y) x = ++i, y = f(x);
        if ((q = mult(prd, max(x,y) - min(x,y), n))) prd = q;
        x = f(x), y = f(f(y));
    }
    return __gcd(prd, n);
}

vector<ll> factor(ll n) {
    if (n == 1) return {};
    if (is_prime(n)) return {n};
    ll x = pollard(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), r.begin(), r.end());
    return l;
}

vector<pair<ll, int>> prime_fact(ll n) {
    vector<ll> ret = factor(n);
    sort(ret.begin(), ret.end());
    vector<pair<ll, int>> pf;
    for (ll p : ret) {
        if (pf.empty() || pf.back().first != p) {
            pf.emplace_back(p, 1);
        }
        else {
            pf.back().second++;
        }
    }
    return pf;
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