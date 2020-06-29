#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

// longest palindrome with center at i
// i - d1[i] + 1, ... , i + d1[i] - 1 :: type = 1
// i - d2[i], ... , i + d2[i] - 1 :: type = 0

vector<int> Manacher(string s, bool type) {
    int n = s.size();
    vector<int> d(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? type : min(d[l + r - i + (type ^ 1)], r - i + 1);
        while (0 <= i - k - (type ^ 1) && i + k < n && s[i - k - (type ^ 1)] == s[i + k]) {
            k++;
        }
        d[i] = k--;
        if (i + k > r) {
            l = i - k - (type ^ 1);
            r = i + k;
        }
    }
    return d;
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
