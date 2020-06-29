#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

// d[i][j] = min(a[i], a[i + 1], ... , a[i + (1 << j) - 1])
// get(l, r) = min(a[l], a[l + 1], ... , a[r])

const int N = 1e5 + 10, L = 20;
int a[N], d[N][L], rem[N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        d[i][0] = i;
    }
    for (int j = 1; j <= L - 1; j++) {
        for (int i = 1; i <= n; i++) {
            if (i + (1 << j) - 1 > n) {
                continue;
            }
            d[i][j] = a[d[i][j - 1]] < a[d[i + (1 << (j - 1))][j - 1]] ? d[i][j - 1] : d[i + (1 << (j - 1))][j - 1];
        }
    }
    for (int i = 1; i <= n; i++) {
        rem[i] = log2(i);
    }
}

int get(int l, int r) {
    int lg = rem[r - l + 1];
    return a[d[l][lg]] < a[d[r - (1 << lg) + 1][lg]] ? d[l][lg] : d[r - (1 << lg) + 1][lg];
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
