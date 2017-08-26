#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int _next(int x, int n) {
    while (x < n) x *= 10;
    return x % n;
}

int get_cycle_len(int n) {
    int slow = 1, fast = 1;

    auto next = [&](int x) { return _next(x, n); };

    while (fast != 0 && next(fast) != 0) {
        slow = next(slow);
        fast = next(next(fast));

        if (slow == fast) break;
    }

    if (fast == 0 || next(fast) == 0) return 0;

    int p = next(slow), res = 1;
    while (p != slow) {
        p = next(p);
        ++res;
    }
    return res;
}

const int N = 1e4;

int cycle_len[N + 1];
int res[N + 1];

int main() {
    for (int i = 3; i <= N; ++i) {
        cycle_len[i] = get_cycle_len(i);
    }

    int cl = 0;
    for (int i = 3; i <= N; ++i) {
        if (cycle_len[i] > cl) {
            cl = cycle_len[i];
            res[i] = i;
        } else res[i] = res[i - 1];
    }

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        cout << res[n - 1] << endl;
    }
    return 0;
}
