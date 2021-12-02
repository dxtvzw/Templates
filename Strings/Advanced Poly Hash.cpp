#include <bits/stdc++.h>

using namespace std;

template<int mod>
class Modular {
public:
    int val;
    Modular() : val(0) {}
    Modular(int new_val) : val(new_val) {
        assert(0 <= val && val < mod);
#warning DELETE THIS ASSERT
    }
    friend Modular operator+(const Modular& a, const Modular& b) {
        if (a.val + b.val >= mod) return a.val + b.val - mod;
        else return a.val + b.val;
    }
    friend Modular operator-(const Modular& a, const Modular& b) {
        if (a.val - b.val < 0) return a.val - b.val + mod;
        else return a.val - b.val;
    }
    friend Modular operator*(const Modular& a, const Modular& b) {
        return 1ll * a.val * b.val % mod;
    }
    friend Modular binpow(Modular a, long long n) {
        Modular res = 1;
        for (; n; n >>= 1) {
            if (n & 1) res *= a;
            a *= a;
        }
        return res;
    }
    /* ALTERNATIVE INVERSE FUNCTION USING EXTENDED EUCLIDEAN ALGORITHM
    friend void gcd(int a, int b, Modular& x, Modular& y) {
        if (a == 0) {
            x = Modular(0);
            y = Modular(1);
            return;
        }
        Modular x1, y1;
        gcd(b % a, a, x1, y1);
        x = y1 - (b / a) * x1;
        y = x1;
    }
    friend Modular inv(const Modular& a) {
        Modular x, y;
        gcd(a.val, mod, x, y);
        return x;
    }
    */
    friend Modular inv(const Modular& a) {
        return binpow(a, mod - 2);
    }
    Modular operator/(const Modular& ot) const {
        return *this * inv(ot);
    }
    Modular& operator++() {
        if (val + 1 == mod) val = 0;
        else ++val;
        return *this;
    }
    Modular operator++(int) {
        Modular tmp = *this;
        ++(*this);
        return tmp;
    }
    Modular operator+() const {
        return *this;
    }
    Modular operator-() const {
        return 0 - *this;
    }
    Modular& operator+=(const Modular& ot) {
        return *this = *this + ot;
    }
    Modular& operator-=(const Modular& ot) {
        return *this = *this - ot;
    }
    Modular& operator*=(const Modular& ot) {
        return *this = *this * ot;
    }
    Modular& operator/=(const Modular& ot) {
        return *this = *this / ot;
    }
    bool operator==(const Modular& ot) const {
        return val == ot.val;
    }
    bool operator!=(const Modular& ot) const {
        return val != ot.val;
    }
    bool operator<(const Modular& ot) const {
        return val < ot.val;
    }
    bool operator>(const Modular& ot) const {
        return val > ot.val;
    }
    explicit operator int() const {
        return val;
    }
};

template<int mod>
istream& operator>>(istream& istr, Modular<mod>& x) {
    return istr >> x.val;
}

template<int mod>
ostream& operator<<(ostream& ostr, const Modular<mod>& x) {
    return ostr << x.val;
}

template <int mod>
struct lazy_segment_tree {
    static const int N = 1e5 + 5;
    Modular<mod> t[2 * N];
    void update(int l, int r, Modular<mod> val) {
        for (l += N, r += N; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) t[l++] += val;
            if (!(r & 1)) t[r--] += val;
        }
    }
    Modular<mod> get(int pos) {
        if (pos == 0) return 0;
        Modular<mod> res = 0;
        for (pos += N; pos > 0; pos >>= 1) {
            res += t[pos];
        }
        return res;
    }
};

template <int mod>
struct PolyHash {
    static const int N = 1e5 + 5;
    static const int V = 1000;
    std::mt19937 rnd;
    int n;
    Modular<mod> p = rnd() % int(sqrt(mod)) + V;
    Modular<mod> pw[N];
    Modular<mod> pref[N];
    lazy_segment_tree<mod> tree, rev_tree;
    void init(int _n, vector<int> a) {
        n = _n;
        pw[0] = 1;
        for (int i = 1; i <= n; i++) {
            tree.t[i + N] = tree.t[i - 1 + N] + pw[i - 1] * a[i - 1];
            pw[i] = pw[i - 1] * p;
        }
        for (int i = 1; i <= n; i++) {
            rev_tree.t[i + N] = rev_tree.t[i - 1 + N] + pw[i - 1] * a[n - i];
        }
    }
    void update(int pos, Modular<mod> val) {
        val = val + mod;
        tree.update(pos, n, val * pw[pos - 1]);
        rev_tree.update(n - pos + 1, n, val * pw[n - pos]);
    }
    bool is_palindrome(int l, int r) {
        return pw[n - r] * (tree.get(r) - tree.get(l - 1)) == pw[l - 1] * (rev_tree.get(n - l + 1) - rev_tree.get(n - r));
    }
    bool cmp(int i, int j, int len) {
        return pw[j] * (tree.get(i + len - 1) - tree.get(i - 1)) == pw[i] * (tree.get(j + len - 1) - tree.get(j - 1));
    }
};

const int m1 = 1000000123;
const int m2 = 1000000321;

PolyHash<m1> h1;
PolyHash<m2> h2;

string s;
vector<int> a;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL_ALIKHAN
    freopen("input.txt", "r", stdin);
#endif

    cin >> s;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        a.push_back(s[i] - 'a');
    }
    h1.init(n, a);
    h2.init(n, a);
    int q;
    cin >> q;
    while (q--) {
        string type;
        cin >> type;
        if (type == "palindrome?") {
            int l, r;
            cin >> l >> r;
            if (h1.is_palindrome(l, r) && h2.is_palindrome(l, r)) {
                cout << "Yes\n";
            }
            else {
                cout << "No\n";
            }
        }
        else {
            int pos;
            char ch;
            cin >> pos >> ch;
            int val = ch - s[pos - 1];
            s[pos - 1] = ch;
            h1.update(pos, val);
            h2.update(pos, val);
        }
    }

#ifdef LOCAL_ALIKHAN
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}