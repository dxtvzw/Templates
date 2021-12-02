#include <bits/stdc++.h>

using namespace std;

std::istream& operator>>(std::istream& istr, __int128_t& val) {
    string s;
    istr >> s;
    val = 0;
    for (char c : s) {
        val = 10 * val + (c - '0');
    }
    return istr;
}

std::ostream& operator<<(std::ostream& dest, __int128_t val) {
    std::ostream::sentry s(dest);
    if (s) {
        __uint128_t tmp = val < 0 ? -val : val;
        char buffer[128];
        char* d = std::end(buffer);
        do {
            --d;
            *d = "0123456789"[tmp % 10];
            tmp /= 10;
        } while (tmp != 0);
        if (val < 0) {
            --d;
            *d = '-';
        }
        int len = std::end(buffer) - d;
        if (dest.rdbuf()->sputn(d, len) != len) {
            dest.setstate(std::ios_base::badbit);
        }
    }
    return dest;
}

template <typename T>
T read_float() {
    string s;
    cin >> s;
    T res = 0;
    long long pw = 1; // be careful with this long long
    for (int i = 0, dot = 0; i < s.size(); i++) {
        if (s[i] == '.') {
            dot = 1;
        }
        else {
            res = res * 10 + (s[i] - '0');
            if (dot) pw *= 10;
        }
    }
    return res / pw;
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