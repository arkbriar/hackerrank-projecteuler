#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int buildPal(int l) {
    vector<int> digits;
    int l_ = l;
    while (l_ != 0) {
        digits.push_back(l_ % 10);
        l_ /= 10;
    }

    int res = l;
    for (auto d : digits) {
        res = res * 10 + d;
    }

    return res;
}

int main() {
    int t;
    cin >> t;
    for (int a0 = 0; a0 < t; a0++) {
        int n;
        cin >> n;

        bool found = false;
        for (int l = 999; l >= 101; --l) {
            int p = buildPal(l);
            if (p >= n) continue;

            for (int i = 101; i < 1000; ++i) {
                if (p % i == 0 && p / i >= 100 && p / i < 1000) {
                    found = true;
                    break;
                }
            }

            if (found) {
                cout << p << endl;
                break;
            }
        }
    }

    return 0;
}
