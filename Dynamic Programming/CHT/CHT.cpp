#include <bits/stdc++.h>

using namespace std;

typedef __int128_t LL;

struct CHT {
    int pointer=0;
    vector<long long> K, B;
    void clear() {
        pointer = 0;
        K.clear();
        B.clear();
    }
    bool bad(int l1, int l2, int l3) {
        return LL(B[l3] - B[l1]) * (K[l1] - K[l2]) < LL(B[l2] - B[l1]) * (K[l1] - K[l3]);
    }
    void add(long long k, long long b) {
        if (!K.empty() && K.back() == k) return;
        K.push_back(k);
        B.push_back(b);
        while (K.size() >= 3 && bad(K.size() - 3, K.size() - 2, K.size() - 1)) {
            K.erase(K.end()-2);
            B.erase(B.end()-2);
        }
    }
    long long getmin(long long x) {
        while (pointer < K.size()-1 && K[pointer+1] * x + B[pointer+1] < K[pointer] * x + B[pointer]) pointer++;
        return K[pointer] * x + B[pointer];
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