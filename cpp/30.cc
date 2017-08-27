#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

long pow_n[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

long fast_pow(long n, int k) {
    long res = 1;
    while (k) {
        if (k & 1) res *= n;
        n *= n;
        k >>= 1;
    }
    return res;
}

long test(const vector<int> &st) {
    long n = 0;
    for (auto &x : st) n += pow_n[x];
    vector<int> digits;
    long n_ = n;
    while (n_) {
        digits.push_back(n_ % 10);
        n_ /= 10;
    }
    sort(digits.begin(), digits.end());
    if (st == digits)
        return n;
    else
        return -1;
}

int main() {
    int n;
    cin >> n;

    for (auto &x : pow_n) x = fast_pow(x, n);

    // detect the upper limit of the num of digits
    long k = 1;
    while (k * pow_n[9] >= fast_pow(10, k)) ++k;

    long res = 0;
    for (int d = 2; d <= k; ++d) {
        // enumerate all possible digits
        // use vector to simulate stack, keep the property that
        // elements in it is non-decreasing
        vector<int> st;
        st.reserve(d);
        while (int(st.size()) != d) st.push_back(0);

        while (!st.empty()) {
            if (int(st.size()) == d) {
                // 0000 is invalid
                if (st.back() != 0) {
                    auto t = test(st);
                    if (t > 0) res += t;
                }
            }

            auto l = st.back();
            st.pop_back();
            if (l < 9) {
                st.push_back(l + 1);
                while (int(st.size()) != d) st.push_back(st.back());
            }
        }
    }

    cout << res << endl;

    return 0;
}
