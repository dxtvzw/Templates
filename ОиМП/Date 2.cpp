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
    static const int first_year = 1970;
    static const int last_year = 2099;
    int days;
    static bool is_leap(int year) {
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
    static int tot_days(int month, int year) {
        if (is_leap(year) && month == 2) {
            return countDays[2] + 1;
        } else {
            return countDays[month];
        }
    }
    static bool is_valid(int day, int month, int year) {
        if (year < first_year || year > last_year) {
            return false;
        } else if (month < 1 || month > 12) {
            return false;
        } else if (day < 0 || day > tot_days(month, year)) {
            return false;
        } else {
            return true;
        }
    }
    static int convert(int day, int month, int year) {
        int res = 0;
        for (int y = first_year; y != year; ++y) {
            res += 365;
            if (is_leap(y)) {
                ++res;
            }
        }
        for (int m = 1; m != month; ++m) {
            res += tot_days(m, year);
        }
        res += day - 1;
        return res;
    }

public:
    Date(int day, int month, int year) {
        if (!is_valid(day, month, year)) {
            throw std::invalid_argument("invalid date");
        } else {
            days = convert(day, month, year);
        }
    }
    const std::vector<int> get_date() const {
        int day = 1;
        int month = 1;
        int year = first_year;
        int tmp_days = days + 1;
        for (int y = first_year; 365 + static_cast<int>(is_leap(y)) < tmp_days; ++y) {
            year = y + 1;
            tmp_days -= 365 + static_cast<int>(is_leap(y));
        }
        for (int m = 1; tot_days(m, year) < tmp_days; ++m) {
            month = m + 1;
            tmp_days -= tot_days(m, year);
        }
        day = tmp_days;
        return {day, month, year};
    }
    const int GetDay() const {
        return get_date()[0];
    }
    const int GetMonth() const {
        return get_date()[1];
    }
    const int GetYear() const {
        return get_date()[2];
    }
    Date& operator++() {
        ++days;
        return *this;
    }
    Date& operator--() {
        --days;
        return *this;
    }
    Date operator+(int x) const {
        auto tmp = *this;
        tmp.days += x;
        return tmp;
    }
    Date operator-(int x) const {
        auto tmp = *this;
        tmp.days -= x;
        return tmp;
    }
    int operator-(const Date& ot) const {
        return days - ot.days;
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
