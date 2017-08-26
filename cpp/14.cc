#include <cmath>
#include <cstdio>
#include <climits>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <stack>
using namespace std;

const int N = 5e6;

int lt[N + 1];

int res[N + 1];

int len(long n) {
    if (lt[n] > 0) return lt[n];

    int res = 0;
    long x = n;

    while (x == n || x > N) {
        if (x & 1) x = 3 * x + 1;
        else x >>= 1;
        ++ res;
    }

    lt[n] = res + len(x);
    return lt[n];
}

int main() {
    int t;
    cin >> t;

    lt[1] = 1;
    res[1] = 1;

    for (int i = 2; i <= N; ++ i) {
        if (len(i) >= len(res[i - 1])) {
            res[i] = i;
        } else res[i] = res[i - 1];
    }

    while (t--) {
        int n;
        cin >> n;
        cout << res[n] << endl;
    }

    return 0;
}
