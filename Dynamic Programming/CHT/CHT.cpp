#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef __int128_t LL;

struct CHT {
    const ll inf = 1e18 + 10;
    vector<long long> K, B;
    void clear() {
        K.clear();
        B.clear();
    }
    bool bad(int l1, int l2, int l3) {
        return LL(B[l3] - B[l1]) * (K[l1] - K[l2]) < LL(B[l2] - B[l1]) * (K[l1] - K[l3]);
    }
    void add(ll k, ll b) {
        if (!K.empty() && K.back() == k) {
            B.back() = min(B.back(), b);
        } else {
            K.push_back(k);
            B.push_back(b);
        }
        while (K.size() >= 3 && bad(K.size() - 3, K.size() - 2, K.size() - 1)) {
            K.erase(K.end() - 2);
            B.erase(B.end() - 2);
        }
    }
    ll getmin(ll x) {
        if (K.empty()) {
            return inf;
        } else {
            int lef = 0, rig = K.size() - 1;
            while (lef < rig) {
                int mid = (lef + rig) / 2;
                if (K[mid] * x + B[mid] > K[mid + 1] * x + B[mid + 1]) {
                    lef = mid + 1;
                } else {
                    rig = mid;
                }
            }
            return K[lef] * x + B[lef];
        }
    }
};

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