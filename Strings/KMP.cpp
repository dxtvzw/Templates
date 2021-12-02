#include <bits/stdc++.h>

using namespace std;

vector<int> calc_pref_func(string s) {
    int n = s.size();
    vector<int> pref(n, 0);
    int border = 0;
    for (int i = 1; i < n; i++) {
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

vector<int> kmp(string pattern, string text) {
    string s = pattern + '$' + text;
    vector<int> pref = calc_pref_func(s);
    int k = pattern.length();
    vector<int> ans;
    for (int i = k + 1; i < s.length(); i++) {
        if (pref[i] == k) ans.push_back(i - 2 * k);
    }
    return ans;
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