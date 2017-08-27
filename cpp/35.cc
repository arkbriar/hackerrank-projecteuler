#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <set>
using namespace std;

const long N = 1e6;
const int NP = 78498;

bool is_prime[N + 1];
long primes[NP];

void fill_primes() {
    fill_n(is_prime, N + 1, true);
    for (int i = 2; i <= sqrt(N); ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= N; j += i) {
                is_prime[j] = false;
            }
        }
    }

    int count = 0;
    for (int i = 2; i <= N && count < NP; ++i) {
        if (is_prime[i]) {
            primes[count++] = i;
        }
    }
}

bool used[N + 1];

int d[6];

bool test_and_add(long p, long &res, int n) {
    int l = 0, p_ = p;
    for (; p_; ++l) {
        d[l] = p_ % 10;
        p_ /= 10;
    }
    reverse(d, d + l);

    set<int> tmp;
    for (int i = 0; i < l; ++ i) {
        long val = 0;
        for (int i = 0; i < l; ++i) {
            val = val * 10 + d[i];
        }
        if (!is_prime[val]) {
            return false;
        } else {
            if (val >= n) continue;
            used[val] = true;
            tmp.insert(val);
        }
        rotate(d, d + 1, d + l);
    }
    res += accumulate(tmp.begin(), tmp.end(), 0);
    return true;
}

int main() {
    fill_primes();

    int n;
    cin >> n;

    long res = 0;
    for (auto p : primes) {
        if (p >= n) break;

        if (used[p]) continue;
        if (p < 10) {
            used[p] = true;
            res += p;
        } else {
            test_and_add(p, res, n);
        }
    }
    cout << res << endl;
    return 0;
}
