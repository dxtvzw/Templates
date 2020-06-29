#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

template <int mod>
struct Modular {
	int val;
	Modular(int new_val = 0) {
	    val = new_val;
	}
	Modular operator +(const Modular& ot) const {
		if (val + ot.val >= mod) return val + ot.val - mod;
		else return val + ot.val;
	}
	Modular operator -(const Modular& ot) const {
		if (val - ot.val < 0) return val - ot.val + mod;
		else return val - ot.val;
	}
	Modular operator *(const Modular& ot) const {
		return 1ll * val * ot.val % mod;
	}
	Modular& operator ++() {
        if (val + 1 == mod) return 0;
        else return val + 1;
	}
	Modular operator ++(int) {
		Modular tmp(*this);
		operator ++();
		return tmp;
	}
	void operator +=(const Modular& ot) {
		val += ot.val;
		if (val >= mod) {
			val -= mod;
		}
	}
	void operator -=(const Modular& ot) {
		val -= ot.val;
		if (val < 0) {
			val += mod;
		}
	}
	void operator *=(const Modular& ot) {
		val = 1ll * val * ot.val % mod;
	}
	bool operator ==(const Modular& ot) const {
		return val == ot.val;
	}
	bool operator !=(const Modular& ot) const {
		return val != ot.val;
	}
};

template <int mod>
ostream& operator <<(ostream& ostr, const Modular<mod>& x) {
	return ostr << x.val;
}

const int mod = 1000000007;
using Mint = Modular<mod>;

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
