#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

const long N = 1e6;
const int NP = 78498;

bool is_prime[N + 1];
int primes[NP];

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
    for (int i = 2; i <= N; ++i) {
        if (is_prime[i]) {
            primes[count++] = i;
        }
    }
}

int special_divisors(int n) {
    if (!(n & 1)) n >>= 1;
    int res = 1;
    for (int i = 0; i < NP && primes[i] * primes[i] <= n; ++i) {
        long p = primes[i];
        int c = 0;
        while (n % p == 0) {
            c++;
            n /= p;
        }
        res *= c + 1;
    }
    if (n != 1) res *= 2;
    return res;
}

int main() {
    int t;
    cin >> t;

    fill_primes();

    while (t--) {
        int n;
        cin >> n;

        // runs 10 times faster than the older version
        for (int i = 1, last = 1;; ++i) {
            auto tmp = special_divisors(i + 1);
            if (tmp * last > n) {
                cout << i * (i + 1) / 2 << endl;
                break;
            }
            last = tmp;
        }
    }

    return 0;
}
