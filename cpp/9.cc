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

int main() {
    int t;
    cin >> t;
    for (int a0 = 0; a0 < t; a0++) {
        int n;
        cin >> n;

        int res = -1;
        for (int a = 1; a < n / 3; ++a) {
            int bpc = n - a;
            if ((a * a) % bpc == 0) {
                int cmb = a * a / bpc;
                if (((cmb + bpc) & 1) != 0) continue;
                int b = (bpc - cmb) / 2, c = (bpc + cmb) / 2;
                res = max(res, a * b * c);
            }
        }
        cout << res << endl;
    }
    return 0;
}
