#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

const int N = 135;
ll t[N][N][N];

void update(int x, int y, int z, ll val) {
    for (int i = x; i < N; i = (i | (i + 1))) {
        for (int j = y; j < N; j = (j | (j + 1))) {
            for (int k = z; k < N; k = (k | (k + 1))) {
                t[i][j][k] += val;
            }
        }
    }
}

ll get(int x, int y, int z) {
    ll res = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
            for (int k = z; k >= 0; k = (k & (k + 1)) - 1) {
                res += t[i][j][k];
            }
        }
    }
    return res;
}

// return sum of t[x][y][z] for all x1 <= x <= x2, y1 <= y <= y2 and z1 <= z <= z2
ll get_range(int x1, int y1, int z1, int x2, int y2, int z2) {
    x1--, y1--, z1--;
    return get(x2, y2, z2) - get(x1, y2, z2) - get(x2, y1, z2) - get(x2, y2, z1) + get(x2, y1, z1) + get(x1, y2, z1) + get(x1, y1, z2) - get(x1, y1, z1);
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
