#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

const int N = 3e5 + 10, sigma = 30;

struct Node {
    int l, r, len;
    int to[sigma];
    int link, dist;
    void clear() {
        l = r = len = link = dist = 0;
        for (int i = 0; i < sigma; i++) {
            to[i] = 0;
        }
    }
};

Node tree[N];
Node root1, root2;

int curNode;
string s;
int sz;

void init() {
    root1.len = -1;
    root1.link = 1;
    root2.len = 0;
    root2.link = 1;
    tree[1] = root1;
    tree[2] = root2;
    sz = 2;
    curNode = 1;
}

void add_node(int idx) {
    int temp = curNode;
    while (!(idx - tree[temp].len >= 1 && s[idx] == s[idx - tree[temp].len - 1])) {
        temp = tree[temp].link;
    }
    if (tree[temp].to[s[idx] - 'a'] != 0) {
        curNode = tree[temp].to[s[idx] - 'a'];
        return;
    }
    tree[temp].to[s[idx] - 'a'] = ++sz;
    tree[sz].len = tree[temp].len + 2;
    tree[sz].r = idx;
    tree[sz].l = idx - tree[sz].len + 1;
    temp = tree[temp].link;
    curNode = sz;
    if (tree[curNode].len == 1) {
        tree[curNode].link = 2;
        tree[curNode].dist = 1;
        return;
    }
    while (!(idx - tree[temp].len >= 1 && s[idx] == s[idx - tree[temp].len - 1])) {
        temp = tree[temp].link;
    }
    tree[curNode].link = tree[temp].to[s[idx] - 'a'];
    tree[curNode].dist = tree[tree[curNode].link].dist + 1;
}
// dp[i] = number of palindromes ending on index i
int dp[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    cin >> s;
    int n = s.size();
    init();
    for (int i = 0; i < n; i++) {
        add_node(i);
        dp[i] = tree[curNode].dist;
    }

#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
