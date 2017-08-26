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

unordered_map<int, int> decomposition(int m) {
    unordered_map<int, int> pf;
    for (int i = 0; i < NP && primes[i] * primes[i] <= m; ++i) {
        long p = primes[i];
        while (m % p == 0) {
            pf[p]++;
            m /= p;
        }
    }
    if (m != 1) pf[m] ++;
    return pf;
}

int divisors(int n) {
    auto lp = decomposition(n), rp = decomposition(n + 1);
    for (auto &e : rp) {
        lp[e.first] += e.second;
    }
    lp[2]--;

    int res = 1;
    for (auto &e : lp) {
        res *= e.second + 1;
    }
    return res;
}

int main() {
    int t;
    cin >> t;

    fill_primes();

    while (t--) {
        int n;
        cin >> n;

        for (int i = 1; ; ++i) {
            if (divisors(i) > n) {
                cout << i * (i + 1) / 2 << endl;
                break;
            }
        }
    }

    return 0;
}
