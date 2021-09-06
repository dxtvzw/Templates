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

	bigint(const string &s) {
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
  ######################################################################
  ##########################    POLYNOMIAL    ##########################
*/

template <typename T>
class ConstPolyIter;

template <typename T>
class Polynomial {
public:
    const T zero = T(0);
    std::vector<T> poly;
    Polynomial& fix_size() {
        while (!poly.empty() && poly.back() == T(0)) {
            poly.pop_back();
        }
        return *this;
    }


    Polynomial(const std::vector<T>& _poly) {
        poly = _poly;
        fix_size();
    }
    Polynomial(const T& c = T(0)) {
        poly = {c};
        fix_size();
    }
    template <typename Iter>
    Polynomial(Iter first, Iter last) {
        while (first != last) {
            poly.push_back(*first++);
        }
        fix_size();
    }
    Polynomial(const Polynomial& ot) {
        poly.resize(ot.Degree() + 1);
        for (int i = 0; i <= ot.Degree(); ++i) {
            poly[i] = ot[i];
        }
        fix_size();
    }
    Polynomial(Polynomial&& ot) {
        poly.resize(ot.Degree() + 1);
        for (int i = 0; i <= ot.Degree(); ++i) {
            poly[i] = ot[i];
        }
        fix_size();
    }
    Polynomial& operator=(const Polynomial& ot) {
        poly.resize(ot.Degree() + 1);
        for (int i = 0; i <= ot.Degree(); ++i) {
            poly[i] = ot[i];
        }
        fix_size();
        return *this;
    }
    bool operator==(const Polynomial& ot) const {
        if (Degree() != ot.Degree()) {
            return false;
        } else {
            for (int i = 0; i <= Degree(); ++i) {
                if ((*this)[i] != ot[i]) {
                    return false;
                }
            }
            return true;
        }
    }
    bool operator!=(const Polynomial& ot) const {
        return !(*this == ot);
    }
    friend bool operator==(const Polynomial<T>& a, const T& b) {
        return a == Polynomial<T>(b);
    }
    friend bool operator==(const T& a, const Polynomial<T>& b) {
        return Polynomial<T>(a) == b;
    }
    friend bool operator!=(const Polynomial<T>& a, const T& b) {
        return a != Polynomial<T>(b);
    }
    friend bool operator!=(const T& a, const Polynomial<T>& b) {
        return Polynomial<T>(a) != b;
    }
    Polynomial operator+(const Polynomial& ot) const {
        Polynomial res = *this;
        if (res.Degree() < ot.Degree()) {
            res.poly.resize(ot.Degree() + 1);
        }
        for (int i = 0; i <= ot.Degree(); ++i) {
            res.poly[i] += ot[i];
        }
        return res.fix_size();
    }
    Polynomial operator-(const Polynomial& ot) const {
        Polynomial res = *this;
        if (res.Degree() < ot.Degree()) {
            res.poly.resize(ot.Degree() + 1);
        }
        for (int i = 0; i <= ot.Degree(); ++i) {
            res.poly[i] -= ot[i];
        }
        return res.fix_size();
    }
    Polynomial operator*(const Polynomial& ot) const {
        if (Degree() == -1 || ot.Degree() == -1) {
            return Polynomial(T(0));
        } else {
            Polynomial res;
            res.poly.resize(Degree() + ot.Degree() + 1);
            for (int i = 0; i <= Degree(); ++i) {
                for (int j = 0; j <= ot.Degree(); ++j) {
                    res.poly[i + j] += poly[i] * ot.poly[j];
                }
            }
            return res;
        }
    }
    friend Polynomial<T> operator+(const Polynomial<T>& a, const T& b) {
        return a + Polynomial<T>(b);
    }
    friend Polynomial<T> operator+(const T& a, const Polynomial<T>& b) {
        return Polynomial<T>(a) + b;
    }
    friend Polynomial<T> operator-(const Polynomial<T>& a, const T& b) {
        return a - Polynomial<T>(b);
    }
    friend Polynomial<T> operator-(const T& a, const Polynomial<T>& b) {
        return Polynomial<T>(a) - b;
    }
    friend Polynomial<T> operator*(const Polynomial<T>& a, const T& b) {
        return a * Polynomial<T>(b);
    }
    friend Polynomial<T> operator*(const T& a, const Polynomial<T>& b) {
        return Polynomial<T>(a) * b;
    }
    Polynomial& operator+=(const Polynomial& ot) {
        return *this = *this + ot;
    }
    Polynomial& operator+=(const T& ot) {
        return *this += Polynomial(ot);
    }
    Polynomial& operator-=(const Polynomial& ot) {
        return *this = *this - ot;
    }
    Polynomial& operator-=(const T& ot) {
        return *this -= Polynomial(ot);
    }
    Polynomial& operator*=(const Polynomial& ot) {
        return *this = *this * ot;
    }
    Polynomial& operator*=(const T& ot) {
        return *this *= Polynomial(ot);
    }
    const T& operator[](int i) const {
        if (i > Degree()) {
            return zero;
        } else {
            return poly[i];
        }
    }
    bool Empty() const {
        return poly.empty();
    }
    int Degree() const {
        if (Empty()) {
            return -1;
        } else {
            return poly.size() - 1;
        }
    }
    T operator()(const T& val) const {
        T res = T(0);
        T pw = 1;
        for (int i = 0; i <= Degree(); ++i) {
            res += poly[i] * pw;
            pw *= val;
        }
        return res;
    }
    ConstPolyIter<T> begin() const {
        return ConstPolyIter<T>(*this, 0);
    }
    ConstPolyIter<T> end() const {
        return ConstPolyIter<T>(*this, Degree() + 1);
    }
    Polynomial operator&(const Polynomial& ot) const {
        if (Degree() == -1) {
            return *this;
        } else if (ot.Degree() == -1) {
            return Polynomial(poly[0]);
        } else {
            Polynomial res(0);
            Polynomial pw(1);
            for (int i = 0; i <= Degree(); ++i) {
                res += poly[i] * pw;
                pw *= ot;
            }
            return res;
        }
    }
    const T& back() const {
        return poly.back();
    }
    Polynomial shift(int d) const {
        if (Degree() == -1 || d == 0) {
            return *this;
        } else {
            Polynomial res(*this);
            res.poly.resize(res.poly.size() + d);
            for (int i = res.Degree(); i >= d; --i) {
                res.poly[i] = res[i - d];
            }
            for (int i = d - 1; i >= 0; --i) {
                res.poly[i] = T(0);
            }
            return res;
        }
    }
};

template<typename T>
Polynomial<T> x_to_nth_power(int n) {
    if (n < 0) {
        return Polynomial<T>();
    } else {
        std::vector<T> coefficients(n + 1, T(0));
        coefficients[n] = T(1);
        return Polynomial(coefficients);
    }
}

template<typename T>
std::pair<Polynomial<T>, Polynomial<T>>
divide(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    Polynomial<T> result, remainder(lhs);
    for (int power = lhs.Degree(); power >= rhs.Degree(); --power) {
        const auto to_subtract = (remainder[power] / rhs[rhs.Degree()])
                                 * x_to_nth_power<T>(power - rhs.Degree());
        remainder -= to_subtract * rhs;
        result += to_subtract;
    }
    return {result, remainder};
}

template<typename T>
Polynomial<T> operator/(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    const auto [d, _] = divide(lhs, rhs);
    return d;
}

template<typename T>
Polynomial<T> operator/=(Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    lhs = lhs / rhs;
    return lhs;
}

template<typename T>
Polynomial<T> operator/=(Polynomial<T>& lhs, const T& rhs) {
    lhs = lhs / Polynomial(rhs);
    return lhs;
}

template<typename T>
Polynomial<T> operator%(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    const auto [_, r] = divide(lhs, rhs);
    return r;
}

template<typename T>
Polynomial<T> operator%=(Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    lhs = lhs % rhs;
    return lhs;
}

template<typename T>
Polynomial<T> operator,(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    auto a(lhs), b(rhs);
    while (b.Degree() >= 0) {
        a %= b;
        std::swap(a, b);
    }
    if (a.Degree() >= 0) {
        auto leading_coefficient = a[a.Degree()];
        a /= leading_coefficient;
    }
    return a;
}

template <typename T>
std::ostream& operator<<(std::ostream& ostr, const Polynomial<T>& p) {
    if (p.Degree() == -1) {
        ostr << "0";
    } else {
        for (int i = p.Degree(); i >= 0; --i) {
            if (p[i] < T(0)) {
                ostr << "-";
                if (p[i] == T(-1)) {
                    if (i > 0) {
                        ostr << "x";
                        if (i > 1) {
                            ostr << "^" << i;
                        }
                    } else {
                        ostr << "1";
                    }
                } else {
                    if (i > 0) {
                        ostr << -p[i] << "*x";
                        if (i > 1) {
                            ostr << "^" << i;
                        }
                    } else {
                        ostr << -p[i];
                    }
                }
            } else if (p[i] > T(0)) {
                if (i < p.Degree()) {
                    ostr << "+";
                }
                if (p[i] == T(1)) {
                    if (i > 0) {
                        ostr << "x";
                        if (i > 1) {
                            ostr << "^" << i;
                        }

                    } else {
                        ostr << "1";
                    }
                } else {
                    if (i > 0) {
                        ostr << p[i] << "*x";
                        if (i > 1) {
                            ostr << "^" << i;
                        }
                    } else {
                        ostr << p[i];
                    }
                }
            }
        }
    }
    return ostr;
}

template <typename T>
class ConstPolyIter {
private:
    const Polynomial<T>& p;
    int ptr;

public:
    explicit ConstPolyIter(const Polynomial<T>& _p, int _ptr) : p(_p), ptr(_ptr) {}
    ConstPolyIter& operator++() {
        ++ptr;
        return *this;
    }
    ConstPolyIter& operator--() {
        --ptr;
        return *this;
    }
    ConstPolyIter& operator+(int x) {
        ptr += x;
        return *this;
    }
    ConstPolyIter& operator-(int x) {
        ptr -= x;
        return *this;
    }
    const T& operator*() const {
        return p[ptr];
    }
    bool operator==(const ConstPolyIter& ot) const {
        return ptr == ot.ptr;
    }
    bool operator!=(const ConstPolyIter& ot) const {
        return ptr != ot.ptr;
    }
};

/*
  ##########################    POLYNOMIAL    ##########################
  ######################################################################
*/

/*
  ################################################################
  ##########################    MINT    ##########################
*/

long long mod;

class Modular {
public:
    long long val;
    Modular(long long new_val = 0) {
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
        return LL(1) * a.val * b.val % mod;
    }
    friend Modular binpow(Modular a, ll n) {
        Modular res = 1;
        for (; n; n >>= 1) {
            if (n & 1) res *= a;
            a *= a;
        }
        return res;
    }
    friend Modular inv(const Modular& a) {
        if (a == 0) return 1;
        return binpow(a, mod - 2);
    }
    Modular operator/(const Modular& ot) const {
        return *this * inv(ot);
    }
    Modular& operator++() {
        if (val + 1 == mod) val = 0;
        else ++val;
        return *this;
    }
    Modular operator++(int) {
        Modular tmp = *this;
        ++(*this);
        return tmp;
    }
    Modular operator+() const {
        return *this;
    }
    Modular operator-() const {
        return 0 - *this;
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
  if (symbol == 32)
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

bigint convert_from_p_system(const vector<uint>& v, uint p) {
    bigint res = 0;
    for (int i = int(v.size()) - 1; i >= 0; i--) {
        res = res * ll(p) + v[i];
    }
    return res;
}

vector<uint> convert_to_p_system(bigint a, uint p) {
    vector<uint> res;
    while (a != 0) {
        res.push_back(a % p);
        a /= p;
    }
    return res;
}

uint mult(uint a, uint b, uint mod) {
    return ull(1) * a * b % mod;
}

uint binpow(uint a, uint n, uint mod) {
    uint res = 1;
    for (; n; n >>= 1) {
        if (n & 1) res = mult(res, a, mod);
        a = mult(a, a, mod);
    }
    return res;
}

pair<uint, uint> code(uint x, uint p, uint g, uint k) {
    uint n = rnd() % 100 + 3;
    /*
    int a, b;
    cin >> a >> b;
    for (int i = 1; i <= 100; i++) {
        if (binpow(g, i, p) == a) {
            n = i;
            break;
        }
    }
    */
    return {binpow(g, n, p), mult(x, binpow(k, n, p), p)};
}

uint decode(uint x, uint y, uint p, uint k) {
    return mult(y, binpow(x, p - 1 - k, p), p);
}

void solve_a() {
    uint p, g, k;
    cin >> p >> g >> k;
    string message;
    getline(cin, message);
    getline(cin, message);
    vector<uint> vec = string_to_vector(message);
    vec = convert_to_p_system(convert_from_p_system(vec, 64), p);
    for (uint x : vec) {
        auto res = code(x, p, g, k);
        cout << res.F << " " << res.S << "\n";
    }
}

void solve_b() {
    uint p, k;
    cin >> p >> k;
    uint x, y;
    vector<uint> res;
    while (cin >> x >> y) {
        res.push_back(decode(x, y, p, k));
    }
    res = convert_to_p_system(convert_from_p_system(res, p), 64);
    cout << vector_to_string(res) << "\n";
}

using Poly = Polynomial<Modular>;

template <typename T>
vector<T> parse_line(const string& line) {
    stringstream ss(line);
    vector<T> res;
    T cur;
    while (ss >> cur) {
        res.pb(cur);
    }
    return res;
}

Poly read_poly() {
    string line;
    getline(cin, line);
    auto tmp = parse_line<long long>(line);
    vector<Modular> res;
    for (long long& x : tmp) {
        res.emplace_back(x);
    }
    return res;
}

Poly mult(const Poly& a, const Poly& b, const Poly& mod) {
    return a * b % mod;
}

Poly binpow(Poly a, uint n, const Poly& mod) {
    Poly res(1);
    for (; n; n >>= 1) {
        if (n & 1) res = mult(res, a, mod);
        a = mult(a, a, mod);
    }
    return res;
}

pair<Poly, Poly> code(const Poly& x, uint p, const Poly& f, const Poly& g, const Poly& k) {
    uint n = rnd() % 100 + 3;
    /*
    Poly a = read_poly();
    Poly b = read_poly();
    for (int i = 1; i <= 200; i++) {
        if (binpow(g, i, f) == a) {
            n = i;
            break;
        }
    }
    */
    return {binpow(g, n, f), mult(x, binpow(k, n, f), f)};
}

void print(const Poly& p) {
    for (int i = 0; i <= p.Degree(); i++) {
        cout << p[i] << " ";
    }
    cout << "\n";
}

void foo(uint p, const Poly& f, const Poly& g, const Poly& k) {
    Poly a = read_poly();
    Poly b = read_poly();
}

void solve_c() {
    uint p;
    cin >> p;
    mod = p;
    string waste;
    getline(cin, waste);
    Poly f = read_poly();
    Poly g = read_poly();
    Poly k = read_poly();
    int n = f.Degree();
    string line;
    getline(cin, line);
    vector<uint> vec = string_to_vector(line);
    vec = convert_to_p_system(convert_from_p_system(vec, 64), p);
    while (vec.size() % n != 0) {
        vec.push_back(0);
    }

    //foo(p, f, g, k);
    //return;

    for (int i = 0; i < vec.size(); i += n) {
        vector<Modular> cur_v;
        for (int j = 0; j < n; j++) {
            cur_v.emplace_back(vec[i + j]);
        }
        Poly cur(cur_v);
        auto res = code(cur, p, f, g, k);
        print(res.F);
        print(res.S);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    solve_c();

#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
