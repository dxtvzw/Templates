#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;
int a[N], tmp[N];

long long count_inversions(int l, int r) {
    if (l == r) {
        return 0;
    }
    int m = (l + r) / 2;
    long long res = 0;
    res += count_inversions(l, m);
    res += count_inversions(m + 1, r);
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) {
        if (a[i] <= a[j]) {
            res += j - m - 1;
            tmp[k++] = a[i++];
        }
        else {
            tmp[k++] = a[j++];
        }
    }
    while (i <= m) {
        res += r - m;
        tmp[k++] = a[i++];
    }
    while (j <= r + 1) {
        tmp[k++] = a[j++];
    }
    for (int i = l; i <= r; i++) {
        a[i] = tmp[i];
    }
    return res;
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
