#include <bits/stdc++.h>

using namespace std;

struct fenwick1d {
    static const int N = 1e6 + 5;
    int t[N];
    void update(int pos, int val) {
        for (int i = pos; i < N; i = i | (i + 1)) {
            t[i] += val;
        }
    }
    int get_pref_sum(int pref) {
        int res = 0;
        for (int i = pref; i >= 0; i = (i & (i + 1)) - 1) {
            res += t[i];
        }
        return res;
    }
    int get(int l, int r) {
        if (l == 0) return get_pref_sum(r);
        else return get_pref_sum(r) - get_pref_sum(l - 1);
    }
};

template <typename T>
struct fenwick2d {
    static const int N = 1e3;
    T t[N][N];
    void update(int x, int y, T val) {
        for (int i = x; i < N; i = (i | (i + 1))) {
            for (int j = y; j < N; j = (j | (j + 1))) {
                t[i][j] += val;
            }
        }
    }
    T get(int x, int y) {
        T res = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
                res += t[i][j];
            }
        }
        return res;
    }
    // return sum of t[x][y] for all x1 <= x <= x2 and y1 <= y <= y2
    T get_range(int x1, int y1, int x2, int y2) {
        x1--, y1--;
        return get(x2, y2) - get(x1, y2) - get(x2, y1) + get(x1, y1);
    }
};

template <typename T>
struct fenwick3d {
    static const int N = 135;
    T t[N][N][N];
    void update(int x, int y, int z, T val) {
        for (int i = x; i < N; i = (i | (i + 1))) {
            for (int j = y; j < N; j = (j | (j + 1))) {
                for (int k = z; k < N; k = (k | (k + 1))) {
                    t[i][j][k] += val;
                }
            }
        }
    }
    T get(int x, int y, int z) {
        T res = 0;
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
    T get_range(int x1, int y1, int z1, int x2, int y2, int z2) {
        x1--, y1--, z1--;
        return get(x2, y2, z2) - get(x1, y2, z2) - get(x2, y1, z2) - get(x2, y2, z1) + get(x2, y1, z1) + get(x1, y2, z1) + get(x1, y1, z2) - get(x1, y1, z1);
    }
};

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