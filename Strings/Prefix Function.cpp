#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

vector<int> calc_pref_func(string s) {
    int n = s.size();
    vector<int> pref(n, 0);
    int border = 0;
    for (int i=1; i<n; i++) {
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
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif



#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
