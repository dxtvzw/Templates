#include <bits/stdc++.h>

using namespace std;

typedef double real_t;

const double eps = 1e-8;

vector<real_t> Gauss(vector<vector<real_t>> a) {
    int n = a.size();
    int m = a[0].size() - 1;
    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; col++) {
        int sel = row;
        for (int i = row; i < n; i++) {
            if (abs(a[i][col]) > abs(a[sel][col])) {
                sel = i;
            }
        }
        if (abs(a[sel][col]) < eps) {
            continue;
        }
        for (int i = col; i <= m; i++) {
            swap(a[sel][i], a[row][i]);
        }
        where[col] = row;
        for (int i = 0; i < n; i++) {
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j = col; j <= m; j++) {
                    a[i][j] -= a[row][j] * c;
                }
            }
        }
        row++;
    }
    vector<real_t> ans(m, 0);
    for (int i = 0; i < m; i++) {
        if (where[i] != -1) {
            ans[i] = a[where[i]][m] / a[where[i]][i];
        }
    }
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < m; j++) {
            sum += ans[j] * a[i][j];
        }
        if (abs(sum - a[i][m]) > eps) {
            // NO SOLUTION
            return {};
        }
    }
    for (int i = 0; i < m; i++) {
        if (where[i] == -1) {
            // INFINITELY MANY SOLUTIONS
            return {};
        }
    }
    // EXACTLY ONE SOLUTION
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