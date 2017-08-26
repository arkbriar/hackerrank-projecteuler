#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

string add(const string& a, const string& b) {
    int i = a.size() - 1, j = b.size() - 1;
    int c = 0;
    string res;

    while (i >= 0 || j >= 0) {
        int d = c;
        c = 0;
        if (i >= 0) {
            d += a[i--] - '0';
        }
        if (j >= 0) {
            d += b[j--] - '0';
        }
        if (d >= 10) {
            d -= 10;
            c = 1;
        }
        res.push_back(d + '0');
    }

    if (c > 0) res.push_back(c + '0');
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    int n;
    cin >> n;

    vector<string> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    auto res = accumulate(nums.begin(), nums.end(), string("0"), add);
    cout << res.substr(0, 10) << endl;
    return 0;
}
