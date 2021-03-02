#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128_t LL;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
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
    Rational operator-() const {
        return Rational(-p, q);
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
istream& operator>>(istream& istr, Rational<T>& r) {
    istr >> r.p;
    r.q = 1;
    return istr;
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
    Matrix(const vector<T>& _data) {
        row = _data.size();
        col = 1;
        data.resize(row);
        for (int i = 0; i < row; i++) {
            data[i].resize(col, 0);
            data[i][0] = _data[i];
        }
    }
    vector<T>& operator[](size_t i) {
        return data[i];
    }
    const vector<T>& operator[](size_t i) const {
        return data[i];
    }
    Matrix transpose() const {
        Matrix res(col, row);
        for (int i = 0; i < res.row; i++) {
            for (int j = 0; j < res.col; j++) {
                res[i][j] = data[j][i];
            }
        }
        return res;
    }
    Matrix operator+(const Matrix& b) const {
        Matrix res(row, col);
        for (int i = 0; i < res.row; i++) {
            for (int j = 0; j < res.col; j++) {
                res[i][j] = data[i][j] + b[i][j];
            }
        }
        return res;
    }
    Matrix operator-(const Matrix& b) const {
        Matrix res(row, col);
        for (int i = 0; i < res.row; i++) {
            for (int j = 0; j < res.col; j++) {
                res[i][j] = data[i][j] - b[i][j];
            }
        }
        return res;
    }
    Matrix operator*(const Matrix& b) const {
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
    Matrix& operator+=(const Matrix& b) {
        return *this = *this + b;
    }
    Matrix& operator-=(const Matrix& b) {
        return *this = *this - b;
    }
    Matrix& operator*=(const Matrix& b) {
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

#define rank my_rank

template <typename T>
int rank(Matrix<T> A) {
    Gauss(A);
    for (int i = 0; i < A.row; i++) {
        bool ok = 0;
        for (int j = 0; j < A.col; j++) {
            if (A[i][j] != T(0)) {
                ok = 1;
                break;
            }
        }
        if (!ok) {
            return i;
        }
    }
    return A.row;
}

template <typename T>
bool is_zero(const Matrix<T>& A) {
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {
            if (A[i][j] != T(0)) {
                return 0;
            }
        }
    }
    return 1;
}

// generates random solution to an equation A * x = 0
template <typename T>
Matrix<T> gen_any_solution(const Matrix<T>& A, int C = 10) {
    Matrix<T> v(A.col, 1);
    vector<int> is_pivot(A.col, -1);
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {
            if (A[i][j] != T(0)) {
                is_pivot[j] = i;
                break;
            }
        }
    }
    for (int j = v.row - 1; j >= 0; j--) {
        if (is_pivot[j] == -1) {
            v[j][0] = int(rand() % (C + C + 1)) - C;
        }
        else {
            for (int i = j + 1; i < v.row; i++) {
                v[j][0] -= A[is_pivot[j]][i] * v[i][0];
            }
        }
    }
    assert(is_zero(A * v));
    return v;
}

// computes basis of ker(A)
template <typename T>
vector<Matrix<T>> get_kernel(Matrix<T> A) {
    Gauss(A);
    vector<Matrix<T>> basis;
    vector<int> is_pivot(A.col, -1);
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {
            if (A[i][j] != T(0)) {
                is_pivot[j] = i;
                break;
            }
        }
    }
    for (int k = 0; k < A.col; k++) {
        if (is_pivot[k] == -1) { // makes this free variable equal to 1 and others to 0
            Matrix<T> v(A.col, 1);
            v[k][0] = 1;
            for (int j = k - 1; j >= 0; j--) {
                if (is_pivot[j] != -1) {
                    v[j][0] -= A[is_pivot[j]][k] * v[k][0];
                }
            }
            basis.push_back(v);
        }
    }
    return basis;
}

// computes basis of Im(A)
template <typename T>
vector<Matrix<T>> get_image(Matrix<T> A) {
    A = A.transpose();
    Gauss(A);
    vector<Matrix<T>> basis;
    for (int i = 0; i < A.row; i++) {
        Matrix<T> v(A.col, 1);
        for (int j = 0; j < A.col; j++) {
            v[j][0] = A[i][j];
        }
        if (!is_zero(v)) {
            basis.push_back(v);
        }
        else {
            break;
        }
    }
    return basis;
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

using Rat = Rational<int64_t>;
using Mat = Matrix<Rat>;

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

