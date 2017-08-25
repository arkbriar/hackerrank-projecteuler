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

int get_max(const string& num, int n, int k) {
    if (n < k) return 0;
    int l = 0, r = 0, tmp = 1;
    while (r - l < k) tmp *= num[r++] - '0';
    int res = tmp;
    while (r < n) {
        int vl = num[l++] - '0', vr = num[r++] - '0';
        tmp = tmp * vr / vl;
        res = max(tmp, res);
    }
    return res;
}

int main() {
    int t;
    cin >> t;
    for (int a0 = 0; a0 < t; a0++) {
        int n;
        int k;
        cin >> n >> k;
        string num;
        cin >> num;

        int res = 0;

        string::size_type l = 0, r = 0;
        while (l < num.size() && num[l] == '0') ++l;

        while (r != string::npos) {
            r = num.find('0', l);
            string s;
            if (r == string::npos) s = num.substr(l);
            else s = num.substr(l, r - l);
            res = max(get_max(s, s.size(), k), res);
            l = r + 1;
            while (l < num.size() && num[l] == '0') ++l;
        }

        cout << res << endl;
    }
    return 0;
}
