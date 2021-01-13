#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//typedef __int128_t LL;
typedef long double ld;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

template <typename T>
struct Rational {
    T p, q;
    Rational(T val) {
        p = val;
        q = 1;
    }
    Rational(T num, T den) {
        p = num;
        q = den;
        fix();
    }
    Rational& fix() {
        if (p == 0 || q == 0) {
            p = 0;
            q = 1;
        }
        else {
            T g = __gcd(p, q);
            p /= g;
            q /= g;
            if (q < 0) {
                p = -p;
                q = -q;
            }
        }
        return *this;
    }
    Rational operator+(const Rational& ot) const {
        return Rational(p * ot.q + q * ot.p, q * ot.q);
    }
    Rational operator-(const Rational& ot) const {
        return Rational(p * ot.q - q * ot.p, q * ot.q);
    }
    Rational operator*(const Rational& ot) const {
        return Rational(p * ot.p, q * ot.q);
    }
    Rational operator/(const Rational& ot) const {
        return Rational(p * ot.q, q * ot.p);
    }
    Rational& operator+=(const Rational& ot) {
        return *this = *this + ot;
    }
    Rational& operator-=(const Rational& ot) {
        return *this = *this - ot;
    }
    Rational& operator*=(const Rational& ot) {
        return *this = *this * ot;
    }
    Rational& operator/=(const Rational& ot) {
        return *this = *this / ot;
    }
    bool operator==(const Rational& ot) const {
        return p == ot.p && q == ot.q;
    }
    bool operator!=(const Rational& ot) const {
        return p != ot.p || q != ot.q;
    }
    bool operator<(const Rational& ot) const {
        return p * ot.q < q * ot.p;
    }
    bool operator>(const Rational& ot) const {
        return p * ot.q > q * ot.p;
    }
};

template <typename T>
Rational<T> abs(const Rational<T>& r) {
    return {abs(r.p), abs(r.q)};
}

template <typename T = long long>
ostream& operator<<(ostream& ostr, const Rational<T>& r) {
    return ostr << "(" << r.p << " / " << r.q << ")";
}

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
    Matrix(vector<vector<T>> _data): data(std::move(_data)) {
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
    Matrix operator+(T val) const {
        Matrix res(row, col);
        for (int i = 0; i < res.row; i++) {
            for (int j = 0; j < res.col; j++) {
                res[i][j] = data[i][j];
            }
            res[i][i] += val;
        }
        return res;
    }
    Matrix operator-(T val) const {
        Matrix res(row, col);
        for (int i = 0; i < res.row; i++) {
            for (int j = 0; j < res.col; j++) {
                res[i][j] = data[i][j];
            }
            res[i][i] -= val;
        }
        return res;
    }
    Matrix operator*(T val) const {
        Matrix res(row, col);
        for (int i = 0; i < res.row; i++) {
            for (int j = 0; j < res.col; j++) {
                res[i][j] = data[i][j] * val;
            }
        }
        return res;
    }
    Matrix& operator+=(Matrix& b) {
        return *this = *this + b;
    }
    Matrix& operator-=(Matrix& b) {
        return *this = *this - b;
    }
    Matrix& operator*=(Matrix& b) {
        return *this = *this * b;
    }
    Matrix& operator+=(T val) {
        return *this = *this + val;
    }
    Matrix& operator-=(T val) {
        return *this = *this - val;
    }
    Matrix& operator*=(T val) {
        return *this = *this * val;
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

// transforms matrix A to its reduced row echelon form using Gaussian elimination and returns its determinant
template <typename T>
T Gauss(Matrix<T>& a) {
    T det = 1;
    for (int row = 0, col = 0; row < a.row && col < a.col; col++) {
        int sel = row;
        for (int i = row; i < a.row; i++) {
            if (abs(a[i][col]) > abs(a[sel][col])) {
                sel = i;
            }
        }
        if (a[sel][col] == 0) {
            continue;
        }
        if (sel != row) {
            det *= T(-1);
        }
        for (int j = col; j < a.col; j++) {
            swap(a[sel][j], a[row][j]);
        }
        for (int i = 0; i < a.row; i++) {
            if (i != row) {
                T c = a[i][col] / a[row][col];
                for (int j = col; j < a.col; j++) {
                    a[i][j] -= a[row][j] * c;
                }
            }
        }
        row++;
    }
    for (int i = 0; i < a.row; i++) {
        T val = 0;
        for (int j = 0; j < a.col; j++) {
            if (a[i][j] != 0) {
                val = T(1) / a[i][j];
                break;
            }
        }
        if (val == 0) {
            det = 0;
        }
        else {
            det /= val;
        }
        for (int j = 0; j < a.col; j++) {
            a[i][j] *= val;
        }
    }
    return det;
}

// inverts matrix A using Gaussian elimination on a connected matrix (A|E)
template <typename T>
Matrix<T> Invert(Matrix<T> a) {
    Matrix<T> tmp(a.row, a.row + a.col);
    for (int i = 0; i < a.row; i++) {
        for (int j = 0; j < a.col; j++) {
            tmp[i][j] = a[i][j];
        }
        tmp[i][i + a.col] = 1;
    }
    Gauss(tmp);
    Matrix<T> res(a.row, a.col);
    for (int i = 0; i < res.row; i++) {
        for (int j = 0; j < res.col; j++) {
            res[i][j] = tmp[i][j + res.row];
        }
    }
    return res;
}

// binary exponentiation of matrix A to the n'th power
template <typename T>
Matrix<T> binpow(Matrix<T> a, int n) {
    if (n < 0) {
        a = Invert(a);
        n = -n;
    }
    Matrix<T> res(a.row, a.col, 1);
    for (; n; n >>= 1) {
        if (n & 1) res *= a;
        a *= a;
    }
    return res;
}

// calculates determinant of matrix a
template <typename T>
T Determinant(Matrix<T> a) {
    return Gauss(a);
}

// checks if mask contains b'th bit in its binary representation
bool getBit(int mask, int b) {
    return mask & (1 << b);
}

// calculates characteristic polynomial of matrix a
template <typename T>
vector<T> Char_poly(Matrix<T> a) {
    int n = a.row;
    vector<T> chi(n + 1, 0);
    for (int mask = 0; mask < (1 << n); mask++) {
        int k = __builtin_popcount(mask); // k is the size of this subset
        Matrix<T> r(n - k, n - k); // r is going to be the remaining submatrix
        for (int i = 0, di = 0; i < n; i++) {
            if (getBit(mask, i)) {
                di++;
                continue;
            }
            for (int j = 0, dj = 0; j < n; j++) {
                if (getBit(mask, j)) {
                    dj++;
                    continue;
                }
                r[i - di][j - dj] = a[i][j];
            }
        }
        chi[k] += Determinant(r);
    }
    for (int i = n - 1; i >= 0; i -= 2) {
        chi[i] *= T(-1);
    }
    return chi;
}

template <typename T>
ostream& operator<<(ostream& ostr, const vector<T>& poly) {
    for (int i = poly.size() - 1; i >= 0; i--) {
        ostr << poly[i] << " x^" << i;
        if (i >= 1) {
            ostr << " + ";
        }
    }
    return ostr;
}

using Mat = Matrix<Rational<int64_t>>;

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
