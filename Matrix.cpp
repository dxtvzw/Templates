#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

template <typename T>
struct Matrix {
    int row, col;
    vector <vector <T>> data;
    void resize(const int& r, const int& c) {
        row = r;
        col = c;
        data.resize(r);
        for (int i = 0; i < r; i++) {
            data[i].resize(c);
        }
    }
    Matrix operator*(const Matrix& y) const {
        Matrix <T> res;
        res.resize(row, y.col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < y.col; j++) {
                res.data[i][j] = 0;
                for (int k = 0; k < col; k++) {
                    res.data[i][j] += data[i][k] * y.data[k][j];
                }
            }
        }
        return res;
    }
};

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
