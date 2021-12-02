#include <bits/stdc++.h>

using namespace std;

typedef complex<long long> point;
#define x real
#define y imag

long long dot(point a, point b) {
    return (conj(a) * b).x();
}

long long f(point a, long long x) {
    return dot(a, {x, 1});
}

const int N = 1e6 + 10;
const long long inf = 1e18;

point line[4 * N];

void build() {
    for (int i = 0; i < 4 * N; i++) line[i] = {0, inf};
}

void add_line(point nw, int v = 1, int l = 0, int r = N) {
    int m = (l + r) / 2;
    bool lef = f(nw, l) < f(line[v], l);
    bool mid = f(nw, m) < f(line[v], m);
    if (mid) swap(line[v], nw);
    if (r - l == 1) return;
    else if (lef != mid) add_line(nw, v + v, l, m);
    else add_line(nw, v + v + 1, m, r);
}

long long get(int x, int v = 1, int l = 0, int r = N) {
    int m = (l + r) / 2;
    if (r - l == 1) return f(line[v], x);
    else if (x < m) return min(f(line[v], x), get(x, v + v, l, m));
    else return min(f(line[v], x), get(x, v + v + 1, m, r));
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