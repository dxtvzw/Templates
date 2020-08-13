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

struct Rect {
    int l, r, d, u;
};

const Rect r_zero = {0, -1, 0, -1};

Rect rect_inter(Rect a, Rect b) {
    int l = max(a.l, b.l), r = min(a.r, b.r), d = max(a.d, b.d), u = min(a.u, b.u);
    if (l <= r && d <= u) return {l, r, d, u};
    else return r_zero;
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
