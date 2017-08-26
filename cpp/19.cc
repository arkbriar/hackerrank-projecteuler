#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

const long days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_leay_year(long y) { return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0); }

long days_to_end(long y, long m, long d) {
    long res = accumulate(days + m + 1, days + 13, 0) + days[m] + 1 - d;
    if (is_leay_year(y) && m <= 2) res++;
    return res;
}

long days_from_begin(long y, long m, long d) {
    long res = accumulate(days + 1, days + m, 0) + d;
    if (is_leay_year(y) && m > 2) res++;
    return res;
}

long multiple_of(long a, long b, long k) {
    if (a > b) return 0;
    long res = (b - a + 1) / k, rem = (b - a + 1) % k;
    if (a % k == 0) {
        if (rem > 0) res++;
    } else {
        if (rem + a % k > k) res++;
    }
    return res;
}

long days_between(long y1, long m1, long d1, long y2, long m2, long d2) {
    if (y1 == y2) return days_from_begin(y2, m2, d2) - days_from_begin(y1, m1, d1) + 1;
    long res = 0;
    res += days_to_end(y1, m1, d1);
    res += 365 * (y2 - y1 - 1);
    res += multiple_of(y1 + 1, y2 - 1, 4) - multiple_of(y1 + 1, y2 - 1, 100) +
           multiple_of(y1 + 1, y2 - 1, 400);
    res += days_from_begin(y2, m2, d2);
    return res;
}

void ceil(long &y, long &m, long &d) {
    if (d == 1) return;

    // otherwise bump one month
    d = 1;
    m++;

    // bump year when m > 12
    if (m > 12) {
        y++;
        m = 1;
    }
}

void floor(long &y, long &m, long &d) { d = 1; }

long solve(long x, long y1, long m1, long y2, long m2) {
    long y = y1, m = m1;

    long res = 0;
    while (y <= y2) {
        bool leap = is_leay_year(y);
        while ((y < y2 && m <= 12) || (y == y2 && m <= m2)) {
            if (x == 0) {
                res++;
            }
            x = x + days[m];
            if (m == 2 && leap) x++;
            x %= 7;
            ++m;
        }
        m = 1;
        y++;
    }

    return res;
}

int main() {
    long t;
    cin >> t;

    while (t--) {
        long y1, m1, d1;
        cin >> y1 >> m1 >> d1;
        long y2, m2, d2;
        cin >> y2 >> m2 >> d2;

        ceil(y1, m1, d1);
        floor(y2, m2, d2);

        // x == 0 denotes d1 m1 y1 is Sunday
        long x = days_between(1900, 1, 1, y1, m1, d1) % 7;

        cout << solve(x, y1, m1, y2, m2) << endl;
    }
    return 0;
}
