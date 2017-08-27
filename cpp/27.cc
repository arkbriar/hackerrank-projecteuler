#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const long N = 2000;
const long NP = 303;

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

long mulmod(long a, long b, long m) {
    long res;
    asm("mulq %2; divq %3" : "=d"(res), "+a"(a) : "S"(b), "c"(m));
    return res;
}

long fast_pow(long a, long b, long m) {
    a %= m;
    long res = 1;
    while (b > 0) {
        if (b & 1) res = mulmod(res, a, m);
        b >>= 1;
        if (b > 0) a = mulmod(a, a, m);
    }
    return res;
}

bool miller_rabin(long n) {
    if (n < 2) return false;

    long r = 0;
    long d = n - 1;
    while ((d & 1) == 0) {
        r++;
        d >>= 1;
    }

    // according to wikipedia, it's enough to test just these numbers
    for (auto a : {2, 3, 5, 7, 11, 13, 17, 19, 23}) {
        long x = fast_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool is_composite = true;
        for (int i = 0; i < r - 1; ++ i) {
            x = mulmod(x, x, n);
            if (x == 1) return false;
            else if (x == n - 1) {
                is_composite = false;
                break;
            }
        }
        if (is_composite) return false;
    }

    return true;
}

int main() {
    fill_primes();

    int n;
    cin >> n;

    int res = 0, res_a, res_b;
    for (int i = 0; i < NP && primes[i] <= n; ++ i) {
        int b = primes[i];
        for (int a = max(-n, 2 - b); a <= n; a ++) {
            int count = 1;
            for (int i = 1;; ++ i) {
                auto x = i * i + a * i + b;
                if (x > 0 && miller_rabin(x)) count++;
                else break;
            }
            if (res < count) {
                res = count;
                res_a = a;
                res_b = b;
            }
        }
    }
    cout << res_a << ' ' << res_b << endl;
    return 0;
}

