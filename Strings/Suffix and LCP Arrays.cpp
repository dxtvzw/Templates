#include <bits/stdc++.h>

using namespace std;

namespace suffix_array {
    // O(n * log(n))
    int n, sigma;
    map<char, int> alph;
    vector<int> order, cls;
    vector<int> new_order, new_cls;
    vector<int> cnt_char;
    vector<int> cnt_doubled;
    void init(int _n, int _sigma = 30) {
        n = _n, sigma = _sigma;
        sigma = _sigma;
        order.resize(n);
        cls.resize(n);
        new_order.resize(n);
        new_cls.resize(n);
        cnt_char.resize(sigma);
        cnt_doubled.resize(n);
        alph['$'] = 0;
        for (char ch = 'a'; ch <= 'z'; ch++) {
            alph[ch] = ch - 'a' + 1;
        }
    }
    void sort_characters(string& s) {
        for (int i = 0; i < sigma; i++) {
            cnt_char[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            cnt_char[alph[s[i]]]++;
        }
        for (int i = 1; i < sigma; i++) {
            cnt_char[i] += cnt_char[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            order[--cnt_char[alph[s[i]]]]  = i;
        }
    }
    void compute_char_classes(string& s) {
        cls[order[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (s[order[i]] != s[order[i - 1]]) {
                cls[order[i]] = cls[order[i - 1]] + 1;
            }
            else {
                cls[order[i]] = cls[order[i - 1]];
            }
        }
    }
    void sort_doubled(int l) {
        for (int i = 0; i < n; i++) {
            cnt_doubled[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            cnt_doubled[cls[i]]++;
        }
        for (int i = 1; i < n; i++) {
            cnt_doubled[i] += cnt_doubled[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            int st = (order[i] - l + n) % n;
            new_order[--cnt_doubled[cls[st]]] = st;
        }
    }
    void update_classes(int l) {
        new_cls[new_order[0]] = 0;
        for (int i = 1; i <= n - 1; i++) {
            int cur = new_order[i], prev = new_order[i - 1];
            int mid = (cur + l) % n, mid_prev = (prev + l) % n;
            if (cls[cur] != cls[prev] || cls[mid] != cls[mid_prev]) {
                new_cls[cur] = new_cls[prev] + 1;
            }
            else {
                new_cls[cur] = new_cls[prev];
            }
        }
    }
    void swap_vectors() {
        swap(order, new_order);
        swap(cls, new_cls);
    }
    vector<int> build(string& s) {
        assert(s.back() == '$');
        init(s.size());
        sort_characters(s);
        compute_char_classes(s);
        int l = 1;
        while (l < n) {
            sort_doubled(l);
            update_classes(l);
            swap_vectors();
            l <<= 1;
        }
        return order;
    }
};

namespace LCP {
    // O(n) (with precomputed suffix array)
    vector<int> pos, lcp;
    int lcp_of_suffixes(string& s, int i, int j, int eq) {
        int val = max(0, eq);
        while (i + val < s.size() && j + val < s.size() && s[i + val] == s[j + val]) {
            val++;
        }
        return val;
    }
    void invert_suffix_array(vector<int>& order) {
        for (int i = 0; i < order.size(); i++) {
            pos[order[i]] = i;
        }
    }
    vector<int> build(string& s, vector<int>& order) {
        int n = s.size(), val = 0;
        pos.resize(n);
        lcp.resize(n - 1);
        invert_suffix_array(order);
        int suf = order[0];
        for (int i = 0; i < n; i++) {
            int idx = pos[suf];
            if (idx == n - 1) {
                val = 0;
            }
            else {
                val = lcp_of_suffixes(s, suf, order[idx + 1], val - 1);
                lcp[idx] = val;
            }
            if (suf == n - 1) suf = 0;
            else suf++;
        }
        return lcp;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL_ALIKHAN
    freopen("input.txt", "r", stdin);
#endif

    string s;
    cin >> s;
    if (s.back() != '$') s += '$';
    vector<int> order = suffix_array::build(s);
    vector<int> lcp = LCP::build(s, order);

#ifdef LOCAL_ALIKHAN
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}