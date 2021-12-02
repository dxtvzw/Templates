#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct Matrix {
    int row, col;
    vector<vector<T>> data;
    Matrix(int _row, int _col, bool is_identity = false) {
        row = _row;
        col = _col;
        data.resize(row, vector<T>(col, 0));
        if (is_identity) {
            assert(row == col);
            for (int i = 0; i < row; i++) {
                data[i][i] = 1;
            }
        }
    }
    Matrix(vector<vector<T>>&& _data): data(std::forward<decltype(_data)>(_data)) {
        row = data.size();
        col = data[0].size();
    }
    vector<T>& operator[](size_t i) {
        return data[i];
    }
    const vector<T>& operator[](size_t i) const {
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