#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <numeric>
using namespace std;

int value(const vector<int>& nums, int s, int e) {
    int res = 0;
    for (int i = s; i < e; ++ i) {
        res = res * 10 + nums[i];
    }
    return res;
}

int main() {
    int n;
    cin >> n;

    int l = (n + 1) / 2;

    vector<int> nums(n);
    for (int i = 0; i < n; ++ i) nums[i] = i + 1;

    set<int> res;
    do {
        for (int i = 1; i < l; ++ i) {
            auto x = value(nums, l, n);
            if (value(nums, 0, i) * value(nums, i, l) == x)
                res.insert(x);
        }
    } while (std::next_permutation(nums.begin(), nums.end()));

    cout << accumulate(res.begin(), res.end(), 0) << endl;

    return 0;
}
