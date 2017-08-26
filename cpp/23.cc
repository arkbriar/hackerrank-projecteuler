#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

const long N = 1e6;
const long NP = 78498;

bool is_prime[N + 1];
long primes[NP];

void fill_primes() {
    fill_n(is_prime, N + 1, true);
    for (long i = 2; i <= sqrt(N); ++i) {
        if (is_prime[i]) {
            for (long j = i * i; j <= N; j += i) {
                is_prime[j] = false;
            }
        }
    }

    long count = 0;
    for (long i = 2; i <= N; ++i) {
        if (is_prime[i]) {
            primes[count++] = i;
        }
    }
}

long fast_pow(long n, long k) {
    long res = 1;
    long n_ = n;
    while (k > 0) {
        if (k & 1) res *= n_;
        n_ *= n_;
        k >>= 1;
    }
    return res;
}

unordered_map<long, long> decomposition(long m) {
    unordered_map<long, long> pf;
    for (long i = 0; i < NP && primes[i] * primes[i] <= m; ++i) {
        long p = primes[i];
        while (m % p == 0) {
            pf[p]++;
            m /= p;
        }
    }
    if (m != 1) pf[m]++;
    return pf;
}

const int MAX_N = 28123;

bool ab[MAX_N + 1];

long sum_of_proper_divisors(long n) {
    auto nf = decomposition(n);

    long res = 1;
    for (auto &e : nf) {
        res *= (fast_pow(e.first, e.second + 1) - 1) / (e.first - 1);
    }

    return res - n;
}

int main() {
    int t;
    cin >> t;

    fill_primes();

    for (int i = 12; i < MAX_N + 1; ++i) {
        ab[i] = sum_of_proper_divisors(i) > i;
    }

    while (t--) {
        int n;
        cin >> n;

        if (n > 28123) cout << "YES" << endl;
        else {
            bool found = false;
            for (int i = 12; i <= n - 12 && i <= n / 2; ++ i) {
                if (ab[i] && ab[n - i]) {
                    found = true;
                    break;
                }
            }
            if (found) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }

    return 0;
}
