#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128_t LL;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define F first
#define S second
#define pb push_back
mt19937 rnd(time(0));

const std::vector<int> countDays = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class Date { // CHECK YEAR BOUNDARIES
private:
    int day, month, year;
    bool is_leap() const {
        if (year % 400 == 0) {
            return true;
        } else if (year % 100 == 0) {
            return false;
        } else if (year % 4 == 0) {
            return true;
        } else {
            return false;
        }
    }
    int tot_days() const {
        if (is_leap() && month == 2) {
            return countDays[2] + 1;
        } else {
            return countDays[month];
        }
    }
    bool is_valid() const {
        if (year < 1970 || year > 2099 || month < 1 || month > 12 || day < 0 || day > tot_days()) {
            return false;
        } else {
            return true;
        }
    }

public:
    Date(int _day, int _month, int _year) : day(_day), month(_month), year(_year) {
        if (!is_valid()) {
            throw std::invalid_argument("invalid date");
        }
    }
    const int& GetDay() const {
        return day;
    }
    const int& GetMonth() const {
        return month;
    }
    const int& GetYear() const {
        return year;
    }
    Date& operator++() {
        if (day < tot_days()) {
            ++day;
        } else if (month < 12) {
            day = 1;
            ++month;
        } else {
            day = 1;
            month = 1;
            ++year;
        }
        return *this;
    }
    Date& operator--() {
        if (day > 1) {
            --day;
        } else if (month > 1) {
            --month;
            day = tot_days();
        } else {
            day = countDays[12];
            month = 12;
            --year;
        }
        return *this;
    }
    Date operator+(int x) const {
        auto tmp = *this;
        while (x > 0) {
            int dif = tmp.tot_days() - tmp.day;
            if (dif == 0) {
                ++tmp;
                --x;
            } else {
                int delta = std::min(dif, x);
                tmp.day += delta;
                x -= delta;
            }
        }
        return tmp;
    }
    Date operator-(int x) const {
        auto tmp = *this;
        while (x > 0) {
            if (tmp.day == 1) {
                --tmp;
                --x;
            } else {
                int delta = std::min(tmp.day - 1,  x);
                tmp.day -= delta;
                x -= delta;
            }
        }
        return tmp;
    }
    int operator-(const Date& ot) const {
        if (*this == ot) {
            return 0;
        } else if (ot < *this) {
            int lef = 1, rig = 100000;
            while (lef < rig) {
                int mid = (lef + rig) / 2;
                if ((*this - (mid + 1)) < ot) {
                    rig = mid;
                } else {
                    lef = mid + 1;
                }
            }
            return lef;
        } else {
            return -(ot - *this);
        }
    }
    bool operator==(const Date& ot) const {
        return day == ot.day && month == ot.month && year == ot.year;
    }
    bool operator<(const Date& ot) const {
        if (year < ot.year) {
            return true;
        } else if (year > ot.year) {
            return false;
        } else if (month < ot.month) {
            return true;
        } else if (month > ot.month) {
            return false;
        } else if (day < ot.day) {
            return true;
        } else {
            return false;
        }
    }
};

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
