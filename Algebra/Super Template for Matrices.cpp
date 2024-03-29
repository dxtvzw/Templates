#include <bits/stdc++.h>

using namespace std;

std::mt19937 rnd;

typedef long double real_t;

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
    friend Rational operator+(const Rational& a, const Rational& b) {
        return Rational(a.p * b.q + a.q * b.p, a.q * b.q);
    }
    friend Rational operator-(const Rational& a, const Rational& b) {
        return Rational(a.p * b.q - a.q * b.p, a.q * b.q);
    }
    friend Rational operator*(const Rational& a, const Rational& b) {
        return Rational(a.p * b.p, a.q * b.q);
    }
    friend Rational operator/(const Rational& a, const Rational& b) {
        return Rational(a.p * b.q, a.q * b.p);
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
    Rational& operator++(int) {
        return *this += 1;
    }
    friend bool operator==(const Rational& a, const Rational& b) {
        return a.p == b.p && a.q == b.q;
    }
    friend bool operator!=(const Rational& a, const Rational& b) {
        return a.p != b.p || a.q != b.q;
    }
    friend bool operator<(const Rational& a, const Rational& b) {
        return a.p * b.q < a.q * b.p;
    }
    friend bool operator>(const Rational& a, const Rational& b) {
        return a.p * b.q > a.q * b.p;
    }
    operator long double() const {
        return real_t(p) / real_t(q);
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
    Matrix(int _row = 0, int _col = 0, bool is_identity = 0) {
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
        return *this + T(-val);
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
    Matrix operator/(T val) const {
        return *this * T(T(1) / val);
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
    bool operator==(const Matrix& ot) const {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (data[i][j] != ot[i][j]) {
                    return 0;
                }
            }
        }
        return 1;
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
        if (a[sel][col] == T(0)) {
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
            if (a[i][j] != T(0)) {
                val = T(1) / a[i][j];
                break;
            }
        }
        if (val == T(0)) {
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
Matrix<T> invert(Matrix<T> a) {
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
    Gauss(A);
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
        a = invert(a);
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
T determinant(Matrix<T> a) {
    return Gauss(a);
}

// checks if mask contains b'th bit in its binary representation
bool getBit(int mask, int b) {
    return mask & (1 << b);
}

// calculates characteristic polynomial of matrix a
template <typename T>
vector<T> char_poly(Matrix<T> a) {
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
        chi[k] += determinant(r);
    }
    for (int i = n - 1; i >= 0; i -= 2) {
        chi[i] *= T(-1);
    }
    return chi;
}

// calculates multiplicity of lambda as a root of minimal polynomial of a
template <typename T>
int min_poly_multiplicity(const Matrix<T> a, T lambda) {
    Matrix<T> b(a.row, a.row, 1);
    for (int i = 1, prev = 0; i <= a.row; i++) {
        b *= a - Matrix<T>(a.row, a.row, 1) * lambda;
        int cur = get_kernel(b).size();
        if (cur == prev) {
            return i - 1;
        }
        prev = cur;
    }
    return 100;
}

// calculates multiplicity of lambda as a root of characteristic polynomial of a
template <typename T>
int char_poly_multiplicity(const Matrix<T> a, T lambda) {
    return get_kernel(binpow(a - Matrix<T>(a.row, a.row, 1) * lambda, a.row)).size();
}

// part of finding Jordan form
template <typename T>
vector<Matrix<T>> add_to_basis(const vector<Matrix<T>>& v, const Matrix<T>& a, T lambda, int l) {
    int n = a.row;
    Matrix<T> b(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < v.size(); j++) {
            b[i][j] = v[j][i][0];
        }
    }
    vector<Matrix<T>> ans;
    Matrix<T> c = binpow(a - Matrix<T>(n, n, 1) * lambda, l);
    vector<Matrix<T>> basis = get_kernel(c);
    for (int j = 0, ptr = v.size(); j < basis.size() && ptr < n; j++) {
        for (int i = 0; i < b.row; i++) {
            b[i][ptr] = basis[j][i][0];
        }
        if (rank(b) == ptr + 1) {
            ans.pb(basis[j]);
            ptr++;
        }
    }
    /*
    for (int j = v.size(); j < k; j++) {
        do {

            for (int i = 0; i < b.row; i++) {
                b[i][j] = T(rnd() % (C + C + 1)) - T(C);
            }
        } while (rank(b) != j + 1 || !is_zero(c * b));
        Matrix<T> cur(b.row, 1);
        for (int i = 0; i < b.row; i++) {
            cur[i][0] = b[i][j];
        }
        ans.pb(cur);
    }
    */
    return ans;
}

// find Jordan basis of a
template <typename T>
Matrix<T> Jordan_basis(const Matrix<T>& a, vector<T> eigen_values) {
    int n = a.row;
    Matrix<T> basis(n, n);
    int ptr = 0;
    for (T lambda : eigen_values) {
        vector<Matrix<T>> vec;
        int k = min_poly_multiplicity(a, lambda);
        vector<vector<Matrix<T>>> cur_basis(k + 1);
        for (int l = k; l >= 1; l--) {
            vector<Matrix<T>> cur = get_kernel(binpow(a - Matrix<T>(n, n, 1) * lambda, l - 1));
            for (const auto& it : vec) {
                cur.pb(it);
            }
            vector<Matrix<T>> nxt = add_to_basis(cur, a, lambda, l);
            for (const auto& it : nxt) {
                vec.pb(it);
            }
            cur_basis[l] = vec;
            for (auto& it : vec) {
                it = (a - Matrix<T>(n, n, 1) * lambda) * it;
            }
        }
        for (int j = 0; j < cur_basis[1].size(); j++) {
            for (int i = 1; i <= k; i++) {
                if (cur_basis[i].size() <= j) {
                    break;
                }
                for (int x = 0; x < n; x++) {
                    basis[x][ptr] = cur_basis[i][j][x][0];
                }
                ptr++;
            }
        }
    }
    return basis;
}

// finds Jordan form
template <typename T>
Matrix<T> Jordan_form(const Matrix<T>& a, vector<T> eigen_values) {
    Matrix<T> b = Jordan_basis(a, eigen_values);
    return invert(b) * a * b;
}

// calculates Jacobi form using angle minors
template <typename T>
Matrix<T> Jacobi_form_slow(const Matrix<T>& b) {
    vector<T> dets = {T(1)};
    int n = b.row;
    for (int i = 1; i <= n; i++) {
        Matrix<T> tmp(i, i);
        for (int x = 0; x < i; x++) {
            for (int y = 0; y < i; y++) {
                tmp[x][y] = b[x][y];
            }
        }
        dets.pb(determinant(tmp));
        if (dets.back() == T(0)) {
            return Matrix<T>(n, n);
        }
    }
    Matrix<T> res(n, n);
    for (int i = 0; i < n; i++) {
        res[i][i] = dets[i + 1] / dets[i];
    }
    return res;
}

// Jacobi plus plus from lectures
template <typename T>
Matrix<T> Jacobi_form_generalized(const Matrix<T>& b) {
    Matrix<T> a = b;
    int n = a.row;
    for (int row = 0; row < n; row++) {
        if (a[row][row] == T(0)) {
            int mem = -1;
            for (int i = row + 1; i < n; i++) {
                if (a[i][row] != T(0)) {
                    mem = i;
                    break;
                }
            }
            if (mem == -1) {
                continue;
            }
            else {
                for (int j = 0; j < n; j++) {
                    a[row][j] += a[mem][j];
                }
                for (int i = 0; i < n; i++) {
                    a[i][row] += a[i][mem];
                }
            }
        }
        for (int i = row + 1; i < n; i++) {
            T cur = a[i][row] / a[row][row];
            for (int j = row; j < n; j++) {
                a[i][j] -= cur * a[row][j];
            }
        }
    }
    Matrix<T> d(n, n);
    for (int i = 0; i < n; i++) {
        d[i][i] = a[i][i];
    }
    return d;
}

// finds Jacobi basis
template <typename T>
Matrix<T> Jacobi_basis(const Matrix<T>& b) {
    Matrix<T> u = b;
    int n = u.row;
    for (int row = 0; row < n; row++) {
        if (u[row][row] == T(0)) {
            return Matrix<T>(n, n);
        }
        else {
            for (int i = row + 1; i < n; i++) {
                T cur = u[i][row] / u[row][row];
                for (int j = row; j < n; j++) {
                    u[i][j] -= cur * u[row][j];
                }
            }
        }
    }
    Matrix<T> d(n, n);
    for (int i = 0; i < n; i++) {
        d[i][i] = u[i][i];
    }
    Matrix<T> v = invert(d) * u;
    return invert(u) * d;
}

// finds Jacobi form
template <typename T>
Matrix<T> Jacobi_form(const Matrix<T>& b) {
    Matrix<T> c = Jacobi_basis(b);
    if (is_zero(c)) {
        return Jacobi_form_generalized(b);
    }
    else {
        return c.transpose() * b * c;
    }
}

// dot product of two column vectors
template <typename T>
T dot(const Matrix<T>& a, const Matrix<T>& b) {
    return (a.transpose() * b)[0][0];
}

// generates random matrix with integer entries from [-C, C]
template <typename T>
Matrix<T> random_matrix(int row, int col, int C = 10) {
    Matrix<T> res(row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            res[i][j] = int(rnd()) % (C + C + 1) - C;
        }
    }
    return res;
}

// finds basis of orthogonal complement of subspace with basis e with respect to a symmetrical bilinear form b
template <typename T>
vector<Matrix<T>> get_orthogonal_complement(const vector<Matrix<T>>& e, const Matrix<T>& b) {
    Matrix<T> tmp(e.size(), b.row);
    for (int i = 0; i < e.size(); i++) {
        for (int j = 0; j < e[i].row; j++) {
            tmp[i][j] = e[i][j][0];
        }
    }
    return get_kernel(tmp * b);
}

template <typename T>
vector<Matrix<T>> get_basis_from_span(const vector<Matrix<T>>& vec) {
    Matrix<T> a(vec.size(), vec.front().row);
    for (int i = 0; i < a.row; i++) {
        for (int j = 0; j < a.col; j++) {
            a[i][j] = vec[i][j][0];
        }
    }
    Gauss(a);
    vector<Matrix<T>> basis;
    for (int i = 0; i < a.row; i++) {
        Matrix<T> cur(a.col, 1);
        for (int j = 0; j < a.col; j++) {
            cur[j][0] = a[i][j];
        }
        if (!is_zero(cur)) {
            basis.pb(cur);
        }
    }
    return basis;
}

// calculates projection of vector a onto vector b
template <typename T>
Matrix<T> proj(const Matrix<T>& a, const Matrix<T>& b) {
    return b * dot(a, b) / dot(b, b);
}

// transforms vectors from vec to an ORTHOGONAL (NOT ORTHONORMAL) basis of their span
template <typename T>
vector<Matrix<T>> gram_schmidt(vector<Matrix<T>> vec) {
    vec = get_basis_from_span(vec);
    vector<Matrix<T>> basis = {vec.front()};
    for (int i = 1; i < vec.size(); i++) {
        Matrix<T> cur = vec[i];
        for (int j = 0; j < i; j++) {
            cur -= proj(vec[i], basis[j]);
        }
        basis.pb(cur);
    }
    return basis;
}

// projection of vector a onto span of vectors from vec
template <typename T>
Matrix<T> proj(const Matrix<T>& a, vector<Matrix<T>> vec) {
    vec = gram_schmidt(vec);
    Matrix<T> res(a.row, a.col);
    for (int i = 0; i < vec.size(); i++) {
        res += vec[i] * dot(a, vec[i]) / dot(vec[i], vec[i]);
    }
    return res;
}

// orthogonal complement of vector a onto span of vectors from vec
template <typename T>
Matrix<T> orth_comp(const Matrix<T>& a, const vector<Matrix<T>>& vec) {
    return a - proj(a, vec);
}

// square of norm of a
template <typename T>
T norm2(const Matrix<T>& a) {
    return dot(a, a);
}

// norm of a
template <typename T>
real_t norm(const Matrix<T>& a) {
    return sqrt(real_t(norm2(a)));
}

// angle between a and b
template <typename T>
real_t angle(const Matrix<T>& a, const Matrix<T>& b) {
    return acos(real_t(dot(a, b)) / norm(a) / norm(b));
}

template <typename T>
real_t angle(const Matrix<T>& a, const vector<Matrix<T>>& vec) {
    return angle(a, proj(a, vec));
}

// square of distance from a to span of vectors from vec
template <typename T>
T dist2(const Matrix<T>& a, const vector<Matrix<T>>& vec) {
    return norm2(orth_comp(a, vec));
}

// distance from a to span of vectors from vec
template <typename T>
real_t dist(const Matrix<T>& a, const vector<Matrix<T>>& vec) {
    return norm(orth_comp(a, vec));
}

using Rat = Rational<int64_t>;
using Mat = Matrix<Rat>;

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