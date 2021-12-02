#include <bits/stdc++.h>

using namespace std;

vector<int> calc_z_func(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i <= n - 1; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

vector<int> calc_pref_func(const string& s) {
    int n = s.size();
    vector<int> pref(n, 0);
    for (int i = 1, border = 0; i <= n - 1; i++) {
        while (s[border] != s[i] && border) {
            border = pref[border - 1];
        }
        if (s[border] == s[i]) {
            border++;
        }
        pref[i] = border;
    }
    return pref;
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