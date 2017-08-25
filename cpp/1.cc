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

long total_sum(long n) { return (n + 1) * n / 2; }

int main() {
    int t;
    cin >> t;
    for (int a0 = 0; a0 < t; a0++) {
        int n;
        cin >> n;

        long a = (n - 1) / 3, b = (n - 1) / 5, c = (n - 1) / 15;
        cout << 3 * total_sum(a) + 5 * total_sum(b) - 15 * total_sum(c) << endl;
    }

    return 0;
}
