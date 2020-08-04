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

struct bigint {
    // BASE * SIZE >= length of the number
    static const long long BASE = 1e9;
    static const long long SIZE = 60;
    long long digits[SIZE];
    bigint() {
        for (int i = 0; i < SIZE; i++) {
            digits[i] = 0;
        }
    }
    bigint(long long x) {
        for (int i = 0; i < SIZE; i++) {
            digits[i] = 0;
        }
        int next = 0;
        while (x) {
            digits[next++] = x % BASE;
            x /= BASE;
        }
    }
    bigint(const bigint& other) {
        for (int i = 0; i < SIZE; i++) {
            digits[i] = other.digits[i];
        }
    }
    bigint& operator=(const bigint& other) {
        for (int i = 0; i < SIZE; i++) {
            digits[i] = other.digits[i];
        }
        return *this;
    }
    void operator+=(const bigint& other) {
        for (int i = 0; i < SIZE; i++) {
            digits[i] += other.digits[i];
        }
        for (int i = 0; i < SIZE - 1; i++) {
            if (digits[i] >= BASE) {
                digits[i] -= BASE;
                digits[i + 1]++;
            }
        }
    }
    bigint operator+(const bigint& other) {
        bigint n(*this);
        n += other;
        return n;
    }
    bigint& operator++() {
        *this += 1;
        return *this;
    }
    void operator-=(const bigint& other) {
        for (int i = 0; i < SIZE; i++) {
            digits[i] -= other.digits[i];
        }
        for (int i = 0; i < SIZE - 1; i++) {
            if (digits[i] < 0) {
                digits[i] += BASE;
                digits[i + 1]--;
            }
        }
    }
    bigint operator-(const bigint& other) {
        bigint n(*this);
        n -= other;
        return n;
    }
    bigint& operator--() {
        *this -= 1;
        return *this;
    }
    void operator*=(const bigint& other) {
        *this = *this * other;
    }
    bigint operator*(const bigint& other) {
        bigint result;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE - i; j++) {
                result.digits[i + j] += digits[i] * other.digits[j];
            }
        }
        for (int i = 0; i < SIZE - 1; i++) {
            result.digits[i + 1] += result.digits[i] / BASE;
            result.digits[i] %= BASE;
        }
        return result;
    }
    void operator/=(long long x) {
        for (int i = SIZE - 1; i >= 0; i--) {
            if (i) {
                digits[i - 1] += (digits[i] % x) * BASE;
            }
            digits[i] /= x;
        }
    }
    bigint operator/(long long x) {
        bigint n(*this);
        n /= x;
        return n;
    }
};

ostream& operator<<(ostream& out, const bigint& num) {
    string result;
    char buffer[10];
    for (int i = bigint::SIZE - 1; i >= 0; i--) {
        sprintf(buffer, "%09d", num.digits[i]);
        result += buffer;
    }
    int first_idx = result.find_first_not_of('0');
    if (first_idx == string::npos) {
        out << "0";
    }
    else {
        out << result.substr(first_idx);
    }
    return out;
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
