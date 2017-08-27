#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const long N = 1e5;

bool used[N + 1];
bool b_used[16 * N + 1];

int main() {
    int n;
    cin >> n;

    long res = 0;
    for (int a = 2; a <= n; ++a) {
        if (used[a]) continue;
        used[a] = true;

        // count for a^b that b in [2, n]
        res += n - 1;

        long x = a, k = 1;
        while (x * a <= n) {
            x *= a;
            k++;
        }

        // count for all a^k, there are how many a^kb that is satisfied, which is to say
        // distinct kb > n, where b in [2, n]
        // here I use quadratic sieve
        // it holds for all a that k <= 16 when n == 10000

        // to be more fast, for those a that a^3 > n && a^2 <= n, count = n - n / k holds.
        // without this optimization, loop will run 406 times when n == 100000
        long count = 0;
        if (k == 2) {
            used[x] = true;
            count = n - n / k;
        } else {
            // the following loop will only run for a <= 46 when n == 100000,
            // for 137 times
            fill_n(b_used + n + 1, (k - 1) * n, false);
            while (k > 1) {
                used[x] = true;
                for (int b = k * (n / k + 1); b <= k * n; b += k) {
                    if (b > n && !b_used[b]) {
                        b_used[b] = true;
                        count++;
                    }
                }
                --k;
                x /= a;
            }
        }

        res += count;
    }

    cout << res << endl;

    return 0;
}
