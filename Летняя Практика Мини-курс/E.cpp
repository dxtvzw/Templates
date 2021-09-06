#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128_t LL;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define F first
#define S second
#define pb push_back
mt19937 rnd(time(0));

/*
  ######################################################################
  #######################   THE   BIG   INT   ##########################
*/
const ll base = 1000000000;
const int base_digits = 9;
struct bigint {
	vector<ll> a;
	int sign;
	/*<arpa>*/
	int size(){
		if(a.empty())return 0;
		int ans=(a.size()-1)*base_digits;
		int ca=a.back();
		while(ca)
			ans++,ca/=10;
		return ans;
	}
	bigint operator ^(const bigint &v){
		bigint ans=1,a=*this,b=v;
		while(!b.isZero()){
			if(b%2)
				ans*=a;
			a*=a,b/=2;
		}
		return ans;
	}
	string to_string(){
		stringstream ss;
		ss << *this;
		string s;
		ss >> s;
		return s;
	}
	int sumof(){
		string s = to_string();
		int ans = 0;
		for(auto c : s)  ans += c - '0';
		return ans;
	}
	/*</arpa>*/
	bigint() :
		sign(1) {
	}

	bigint(long long v) {
		*this = v;
	}

	bigint(const string& s) {
		read(s);
	}

	void operator=(const bigint &v) {
		sign = v.sign;
		a = v.a;
	}

	void operator=(long long v) {
		sign = 1;
		a.clear();
		if (v < 0)
			sign = -1, v = -v;
		for (; v > 0; v = v / base)
			a.push_back(v % base);
	}

	bigint operator+(const bigint &v) const {
		if (sign == v.sign) {
			bigint res = v;
            ll carry = 0;
			for (int i = 0; i < (int) max(a.size(), v.a.size()) || carry; ++i) {
				if (i == (int) res.a.size())
					res.a.push_back(0);
				res.a[i] += carry + (i < (int) a.size() ? a[i] : 0);
				carry = res.a[i] >= base;
				if (carry)
					res.a[i] -= base;
			}
			return res;
		}
		return *this - (-v);
	}

	bigint operator-(const bigint &v) const {
		if (sign == v.sign) {
			if (abs() >= v.abs()) {
				bigint res = *this;
				ll carry = 0;
				for (int i = 0; i < (int) v.a.size() || carry; ++i) {
					res.a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
					carry = res.a[i] < 0;
					if (carry)
						res.a[i] += base;
				}
				res.trim();
				return res;
			}
			return -(v - *this);
		}
		return *this + (-v);
	}

	void operator*=(long long v) {
		if (v < 0)
			sign = -sign, v = -v;
		if(v > base){
			*this = *this * (v / base) * base + *this * (v % base);
			return ;
		}
		ll carry = 0;
		for (int i = 0; i < (int) a.size() || carry; ++i) {
			if (i == (int) a.size())
				a.push_back(0);
			long long cur = a[i] * (long long) v + carry;
			carry = (ll) (cur / base);
			a[i] = (ll) (cur % base);
			//asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
		}
		trim();
	}

	bigint operator*(long long v) const {
		bigint res = *this;
		res *= v;
		return res;
	}

	friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {
		ll norm = base / (b1.a.back() + 1);
		bigint a = a1.abs() * norm;
		bigint b = b1.abs() * norm;
		bigint q, r;
		q.a.resize(a.a.size());

		for (int i = a.a.size() - 1; i >= 0; i--) {
			r *= base;
			r += a.a[i];
			ll s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
			ll s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
			ll d = ((long long) base * s1 + s2) / b.a.back();
			r -= b * d;
			while (r < 0)
				r += b, --d;
			q.a[i] = d;
		}

		q.sign = a1.sign * b1.sign;
		r.sign = a1.sign;
		q.trim();
		r.trim();
		return make_pair(q, r / norm);
	}

	bigint operator/(const bigint &v) const {
		return divmod(*this, v).first;
	}

	bigint operator%(const bigint &v) const {
		return divmod(*this, v).second;
	}

	void operator/=(long long v) {
	    ll rem = 0;
		for (int i = (int) a.size() - 1; i >= 0; --i) {
			long long cur = a[i] + rem * (long long) base;
			a[i] = (long long) (cur / v);
			rem = (long long) (cur % v);
		}
		trim();
	}

	bigint operator/(long long v) const {
		bigint res = *this;
		res /= v;
		return res;
	}

	long long operator%(long long v) const {
		long long m = 0;
		for (int i = a.size() - 1; i >= 0; --i)
			m = (a[i] + m * (LL) base) % v;
		return m;
	}

	void operator+=(const bigint &v) {
		*this = *this + v;
	}
	void operator-=(const bigint &v) {
		*this = *this - v;
	}
	void operator*=(const bigint &v) {
		*this = *this * v;
	}
	void operator/=(const bigint &v) {
		*this = *this / v;
	}

	bool operator<(const bigint &v) const {
		if (sign != v.sign)
			return sign < v.sign;
		if (a.size() != v.a.size())
			return a.size() * sign < v.a.size() * v.sign;
		for (int i = a.size() - 1; i >= 0; i--)
			if (a[i] != v.a[i])
				return a[i] * sign < v.a[i] * sign;
		return false;
	}

	bool operator>(const bigint &v) const {
		return v < *this;
	}
	bool operator<=(const bigint &v) const {
		return !(v < *this);
	}
	bool operator>=(const bigint &v) const {
		return !(*this < v);
	}
	bool operator==(const bigint &v) const {
		return !(*this < v) && !(v < *this);
	}
	bool operator!=(const bigint &v) const {
		return *this < v || v < *this;
	}

	void trim() {
		while (!a.empty() && !a.back())
			a.pop_back();
		if (a.empty())
			sign = 1;
	}

	bool isZero() const {
		return a.empty() || (a.size() == 1 && !a[0]);
	}

	bigint operator-() const {
		bigint res = *this;
		res.sign = -sign;
		return res;
	}

	bigint abs() const {
		bigint res = *this;
		res.sign *= res.sign;
		return res;
	}

	long long longValue() const {
		long long res = 0;
		for (int i = a.size() - 1; i >= 0; i--)
			res = res * base + a[i];
		return res * sign;
	}

	friend bigint gcd(const bigint &a, const bigint &b) {
		return b.isZero() ? a : gcd(b, a % b);
	}
	friend bigint lcm(const bigint &a, const bigint &b) {
		return a / gcd(a, b) * b;
	}

	void read(const string &s) {
		sign = 1;
		a.clear();
		int pos = 0;
		while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
			if (s[pos] == '-')
				sign = -sign;
			++pos;
		}
		for (int i = s.size() - 1; i >= pos; i -= base_digits) {
			int x = 0;
			for (int j = max(pos, i - base_digits + 1); j <= i; j++)
				x = x * 10 + s[j] - '0';
			a.push_back(x);
		}
		trim();
	}

	friend istream& operator>>(istream &stream, bigint &v) {
		string s;
		stream >> s;
		v.read(s);
		return stream;
	}

	friend ostream& operator<<(ostream &stream, const bigint &v) {
		if (v.sign == -1)
			stream << '-';
		stream << (v.a.empty() ? 0 : v.a.back());
		for (int i = (int) v.a.size() - 2; i >= 0; --i)
			stream << setw(base_digits) << setfill('0') << v.a[i];
		return stream;
	}

	static vector<ll> convert_base(const vector<ll> &a, int old_digits, int new_digits) {
		vector<long long> p(max(old_digits, new_digits) + 1);
		p[0] = 1;
		for (int i = 1; i < (int) p.size(); i++)
			p[i] = p[i - 1] * 10;
		vector<ll> res;
		long long cur = 0;
		int cur_digits = 0;
		for (int i = 0; i < (int) a.size(); i++) {
			cur += a[i] * p[cur_digits];
			cur_digits += old_digits;
			while (cur_digits >= new_digits) {
				res.push_back(ll(cur % p[new_digits]));
				cur /= p[new_digits];
				cur_digits -= new_digits;
			}
		}
		res.push_back((ll) cur);
		while (!res.empty() && !res.back())
			res.pop_back();
		return res;
	}

	typedef vector<long long> vll;

	static vll karatsubaMultiply(const vll &a, const vll &b) {
		int n = a.size();
		vll res(n + n);
		if (n <= 32) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					res[i + j] += a[i] * b[j];
			return res;
		}

		int k = n >> 1;
		vll a1(a.begin(), a.begin() + k);
		vll a2(a.begin() + k, a.end());
		vll b1(b.begin(), b.begin() + k);
		vll b2(b.begin() + k, b.end());

		vll a1b1 = karatsubaMultiply(a1, b1);
		vll a2b2 = karatsubaMultiply(a2, b2);

		for (int i = 0; i < k; i++)
			a2[i] += a1[i];
		for (int i = 0; i < k; i++)
			b2[i] += b1[i];

		vll r = karatsubaMultiply(a2, b2);
		for (int i = 0; i < (int) a1b1.size(); i++)
			r[i] -= a1b1[i];
		for (int i = 0; i < (int) a2b2.size(); i++)
			r[i] -= a2b2[i];

		for (int i = 0; i < (int) r.size(); i++)
			res[i + k] += r[i];
		for (int i = 0; i < (int) a1b1.size(); i++)
			res[i] += a1b1[i];
		for (int i = 0; i < (int) a2b2.size(); i++)
			res[i + n] += a2b2[i];
		return res;
	}

	bigint operator*(const bigint &v) const {
		vector<ll> a6 = convert_base(this->a, base_digits, 6);
		vector<ll> b6 = convert_base(v.a, base_digits, 6);
		vll a(a6.begin(), a6.end());
		vll b(b6.begin(), b6.end());
		while (a.size() < b.size())
			a.push_back(0);
		while (b.size() < a.size())
			b.push_back(0);
		while (a.size() & (a.size() - 1))
			a.push_back(0), b.push_back(0);
		vll c = karatsubaMultiply(a, b);
		bigint res;
		res.sign = sign * v.sign;
		ll carry = 0;
		for (int i = 0; i < (int) c.size(); i++) {
			long long cur = c[i] + carry;
			res.a.push_back((ll) (cur % 1000000));
			carry = (ll) (cur / 1000000);
		}
		res.a = convert_base(res.a, 6, base_digits);
		res.trim();
		return res;
	}
};
/*
  #######################   THE   BIG   INT   ##########################
  ######################################################################
*/

/*
  ################################################################
  ##########################    MINT    ##########################
*/

bigint mod;

class Modular {
public:
    bigint val;
    Modular(bigint new_val = 0) {
        val = new_val;
        if (val < 0) val += mod;
        if (val >= mod) val -= mod;
    }
    friend Modular operator+(const Modular& a, const Modular& b) {
        if (a.val + b.val >= mod) return a.val + b.val - mod;
        else return a.val + b.val;
    }
    friend Modular operator-(const Modular& a, const Modular& b) {
        if (a.val - b.val < 0) return a.val - b.val + mod;
        else return a.val - b.val;
    }
    friend Modular operator*(const Modular& a, const Modular& b) {
        return a.val * b.val % mod;
    }
    friend Modular binpow(Modular a, bigint n) {
        Modular res(1);
        for (; n > 0; n /= 2) {
            if (n % 2 == 1) res *= a;
            a *= a;
        }
        return res;
    }
    friend Modular inv(const Modular& a) {
        if (a.val.isZero()) return Modular(1);
        return binpow(a, mod - 2);
    }
    Modular operator/(const Modular& ot) const {
        return *this * inv(ot);
    }
    Modular operator+() const {
        return *this;
    }
    Modular operator-() const {
        return Modular(0) - *this;
    }
    Modular& operator+=(const Modular& ot) {
        return *this = *this + ot;
    }
    Modular& operator-=(const Modular& ot) {
        return *this = *this - ot;
    }
    Modular& operator*=(const Modular& ot) {
        return *this = *this * ot;
    }
    Modular& operator/=(const Modular& ot) {
        return *this = *this / ot;
    }
    bool operator==(const Modular& ot) const {
        return val == ot.val;
    }
    bool operator!=(const Modular& ot) const {
        return val != ot.val;
    }
    bool operator<(const Modular& ot) const {
        return val < ot.val;
    }
    bool operator>(const Modular& ot) const {
        return val > ot.val;
    }
    friend Modular sqrt(const Modular& a) {
        return binpow(a, (mod + 1) / 4);
    }
};

istream& operator>>(istream& istr, Modular& x) {
    return istr >> x.val;
}

ostream& operator<<(ostream& ostr, const Modular& x) {
    return ostr << x.val;
}

/*
  ##########################    MINT    ##########################
  ################################################################
*/

int char_to_int(char symbol) {
  if (symbol >= 48 && symbol <= 57)
    return symbol - 48;
  if (symbol >= 65 && symbol <= 90)
    return symbol - 55;
  if (symbol >= 97 && symbol <= 122)
    return symbol - 61;
  if (symbol == 95) // was 32 for space symbol
    return 62;
  if (symbol == 46)
    return 63;
  return 64;
}

char int_to_char(int val) {
    static bool flag = 0;
    static char mem[300];
    if (!flag) {
        flag = 1;
        for (char ch = 0; ch <= 122; ch++) {
            mem[char_to_int(ch)] = ch;
        }
    }
    return mem[val];
}

vector<uint> string_to_vector(const string& s) {
    vector<uint> res;
    for (char ch : s) {
        res.push_back(char_to_int(ch));
    }
    return res;
}

string vector_to_string(const vector<uint>& v) {
    string res;
    for (uint x : v) {
        res += int_to_char(x);
    }
    return res;
}

bigint convert_from_p_system(const vector<uint>& v, bigint p) {
    bigint res = 0;
    for (int i = int(v.size()) - 1; i >= 0; i--) {
        res = res * p + v[i];
    }
    return res;
}

vector<bigint> convert_to_p_system(bigint a, bigint p) {
    vector<bigint> res;
    while (a != 0) {
        res.push_back(a % p);
        a /= p;
    }
    return res;
}

bigint binpow(bigint a, uint n) {
    bigint res = 1;
    for (; n; n >>= 1) {
        if (n & 1) res *= a;
        a *= a;
    }
    return res;
}

Modular coef_a, coef_b;

struct Point {
    bool is_inf = 0;
    Modular x, y;
    Point() : is_inf(1) {}
    Point(const string& _x, const string& _y) : x(_x), y(_y) {}
    Point(const bigint& _x, const bigint& _y) : x(_x), y(_y) {}
    Point(const Modular& _x, const Modular& _y) : x(_x), y(_y) {}
    friend Point operator*(const Point& a, const Point& b) {
        if (a.is_inf) return b;
        else if (b.is_inf) return a;
        else if (a.x == b.x) {
            if (a.y == b.y) {
                if (a.y.val.isZero()) {
                    return Point();
                }
                else {
                    Modular k = (Modular(3) * a.x * a.x + coef_a) / (Modular(2) * a.y);
                    Modular X = k * k - Modular(2) * a.x;
                    Modular Y = -k * (X - a.x) - a.y;
                    return {X, Y};
                }
            }
            else {
                return Point();
            }
        }
        else {
            Modular k = (b.y - a.y) / (b.x - a.x);
            Modular X = k * k - a.x - b.x;
            Modular Y = -k * (X - a.x) - a.y;
            return {X, Y};
        }
    }
    Point& operator*=(const Point& ot) {
        return *this = *this * ot;
    }
    friend Point binpow(Point a, bigint n) {
        Point res;
        for (; n > 0; n /= 2) {
            if (n % 2 == 1) res *= a;
            a *= a;
        }
        return res;
    }
};

ostream& operator<<(ostream& ostr, const Point& p) {
    if (p.is_inf) return ostr << "Z";
    else return ostr << p.x << " " << p.y;
}

pair<Point, Point> code(const Point& x, const Point& g, const Point& pub_key) {
    int n = 1;
    return {binpow(g, n), x * binpow(pub_key, n)};
}

Point decode(const Point& x, const Point& y, const bigint& ord, const bigint& priv_key) {
    return y * binpow(x, ord - priv_key);
}

bool is_on_curve(const Point& a) {
    return a.y * a.y == a.x * a.x * a.x + coef_a * a.x + coef_b;
}

void solve_e() {
    bigint p = binpow(bigint(2), 256) - binpow(bigint(2), 224) + binpow(bigint(2), 192) + binpow(bigint(2), 96) - 1;
    mod = p;
    bigint a = p - 3;
    bigint b("41058363725152142129326129780047268409114441015993725554835256314039467401291");
    coef_a = a;
    coef_b = b;
    Point g("48439561293906451759052585252797914202762949526041747995844080717082404635286",
             "36134250956749795798585127919587881956611106672985015071877198253568414405109");
    bigint ord("115792089210356248762697446949407573529996955224135760342422259061068512044369");
    string pub_x, pub_y;
    cin >> pub_x >> pub_y;
    Point pub(pub_x, pub_y);
    int n;
    cin >> n;
    //Modular kek = sqrt(g.x);
    //assert(kek * kek == g.x);
    //return;
    while (n--) {
        string message;
        cin >> message;
        vector<uint> vec_kek = string_to_vector(message);
        Modular cur_x = convert_from_p_system(vec_kek, 64);
        Modular cur_y = sqrt(cur_x * cur_x * cur_x + coef_a * cur_x + coef_b);
        Point cur(cur_x, cur_y);
        //assert(is_on_curve(cur));
        auto res = code(cur, g, pub);
        cout << res.F << "\n";
        cout << res.S << "\n";
        //assert(is_on_curve(res.F));
        //assert(is_on_curve(res.S));
    }
}

void solve_f() {
    bigint p = binpow(bigint(2), 256) - binpow(bigint(2), 224) + binpow(bigint(2), 192) + binpow(bigint(2), 96) - 1;
    mod = p;
    bigint a(-3);
    bigint b("41058363725152142129326129780047268409114441015993725554835256314039467401291");
    coef_a = a;
    coef_b = b;
    Point g("48439561293906451759052585252797914202762949526041747995844080717082404635286",
             "36134250956749795798585127919587881956611106672985015071877198253568414405109");
    bigint priv_key;
    cin >> priv_key;
    int n;
    cin >> n;
    while (n--) {
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    solve_e();

#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
