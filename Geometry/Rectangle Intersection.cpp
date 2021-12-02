#include <bits/stdc++.h>

using namespace std;

struct Rect {
    int l, r, d, u;
};

const Rect r_zero = {0, -1, 0, -1};

Rect rect_inter(Rect a, Rect b) {
    int l = max(a.l, b.l), r = min(a.r, b.r), d = max(a.d, b.d), u = min(a.u, b.u);
    if (l <= r && d <= u) return {l, r, d, u};
    else return r_zero;
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