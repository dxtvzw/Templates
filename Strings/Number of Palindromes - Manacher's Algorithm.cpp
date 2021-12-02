#include <bits/stdc++.h>

using namespace std;

// longest palindrome with center at i
// i - d1[i] + 1, ... , i + d1[i] - 1 :: type = 1
// i - d2[i], ... , i + d2[i] - 1 :: type = 0

vector<int> Manacher(string s, bool type) {
    int n = s.size();
    vector<int> d(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? type : min(d[l + r - i + !type], r - i + 1);
        while (0 <= i - k - !type && i + k < n && s[i - k - !type] == s[i + k]) {
            k++;
        }
        d[i] = k--;
        if (i + k > r) {
            l = i - k - !type;
            r = i + k;
        }
    }
    return d;
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