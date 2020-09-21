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

template <typename T>
struct Matrix {
    int row, col;
    vector<vector<T>> data;
    Matrix(int _row, int _col, bool is_identity = 0) {
        row = _row;
        col = _col;
        data.resize(row);
        for (int i = 0; i < row; i++) {
            data[i].resize(col, 0);
        }
        if (is_identity) {
            for (int i = 0; i < row; i++) {
                data[i][i] = 1;
            }
        }
    }
    vector<T>& operator[](int i) {
        return data[i];
    }
    Matrix operator+(Matrix& b) const {
        Matrix res(row, col);
        for (int i = 0; i < res.row; i++) {
            for (int j = 0; j < res.col; j++) {
                res[i][j] = data[i][j] + b[i][j];
            }
        }
        return res;
    }
    Matrix operator-(Matrix& b) const {
        Matrix res(row, col);
        for (int i = 0; i < res.row; i++) {
            for (int j = 0; j < res.col; j++) {
                res[i][j] = data[i][j] - b[i][j];
            }
        }
        return res;
    }
    Matrix operator*(Matrix& b) const {
        Matrix res(row, b.col);
        for (int i = 0; i < res.row; i++) {
            for (int j = 0; j < res.col; j++) {
                for (int k = 0; k < col; k++) {
                    res[i][j] += data[i][k] * b[k][j];
                }
            }
        }
        return res;
    }
    void operator+=(Matrix& b) {
        *this = *this + b;
    }
    void operator-=(Matrix& b) {
        *this = *this - b;
    }
    void operator*=(Matrix& b) {
        *this = *this * b;
    }
};

template <typename T>
istream& operator>>(istream& istr, Matrix<T>& a) {
    for (int i = 0; i < a.row; i++) {
        for (int j = 0; j < a.col; j++) {
            istr >> a[i][j];
        }
    }
    return istr;
}

template <typename T>
ostream& operator<<(ostream& ostr, const Matrix<T>& a) {
    for (int i = 0; i < a.row; i++) {
        if (i != 0) ostr << "\n";
        for (int j = 0; j < a.col; j++) {
            if (j != 0) ostr << " ";
            ostr << a[i][j];
        }
    }
    return ostr;
}

template <typename T>
Matrix<T> binpow(Matrix<T> a, int n) {
    Matrix<T> res(a.row, a.col, 1);
    for (; n; n >>= 1) {
        if (n & 1) res *= a;
        a *= a;
    }
    return res;
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
