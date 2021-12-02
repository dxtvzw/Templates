#include <bits/stdc++.h>

using namespace std;

const int N = 135;
long long t[N][N][N];

void update(int x, int y, int z, long long val) {
    for (int i = x; i < N; i = (i | (i + 1))) {
        for (int j = y; j < N; j = (j | (j + 1))) {
            for (int k = z; k < N; k = (k | (k + 1))) {
                t[i][j][k] += val;
            }
        }
    }
}

long long get(int x, int y, int z) {
    long long res = 0;
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
long long get_range(int x1, int y1, int z1, int x2, int y2, int z2) {
    x1--, y1--, z1--;
    return get(x2, y2, z2) - get(x1, y2, z2) - get(x2, y1, z2) - get(x2, y2, z1) + get(x2, y1, z1) + get(x1, y2, z1) + get(x1, y1, z2) - get(x1, y1, z1);
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