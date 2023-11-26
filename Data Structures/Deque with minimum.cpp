#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct MinDeque {
    const int inf = 1e9 + 10;
    int total_size = 0;
    deque<pair<int, int>> data;
    deque<pair<int, int>> suf_min;
    void push_back(int val) {
        total_size++;
        auto cur = make_pair(val, -total_size);
        while (!suf_min.empty() && suf_min.back() > cur) {
            suf_min.pop_back();
        }
        data.push_back(cur);
        suf_min.push_back(cur);
    }
    void pop_front() {
        if (!data.empty()) {
            if (suf_min.front() == data.front()) {
                suf_min.pop_front();
            }
            data.pop_front();
        }
    }
    int get_min() const {
        if (data.empty()) {
            return inf;
        } else {
            return suf_min.front().first;
        }
    }
    size_t size() const {
        return data.size();
    }
    void clear() {
        total_size = 0;
        data.clear();
        suf_min.clear();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif



#ifdef LOCAL
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
}