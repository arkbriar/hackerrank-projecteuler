#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cassert>
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

// ensure that a * b / m is not larger than 2^64,
// otherwise you will get a SIGFPE
long mulmod(long a, long b, long m) {
    long res;
    asm("mulq %2; divq %3" : "=d"(res), "+a"(a) : "S"(b), "c"(m));
    return res;
}

// pow mod
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

// accurate pow, ensure that n^k is not larger than 2^63 - 1
long fast_pow(long n, int k) {
    long res = 1;
    long n_ = n;
    while (k > 0) {
        if (k & 1) res *= n_;
        n_ *= n_;
        k >>= 1;
    }
    return res;
}

// prime test for nums under 2^64, accurate
bool miller_rabin(long n) {
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
        for (int i = 0; i < r - 1; ++i) {
            x = mulmod(x, x, n);
            if (x == 1)
                return false;
            else if (x == n - 1) {
                is_composite = false;
                break;
            }
        }
        if (is_composite) return false;
    }

    return true;
}

long gcd(long a, long b) {
    long t;
    while (b != 0) {
        t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// pollard rho
long _g(long x, long n) { return (mulmod(x, x, n) + 1) % n; }
pair<long, long> pollard_rho(long n) {
    pair<long, long> res;

    auto g = [&](long x) { return _g(x, n); };
    long x = 2, y = 2, d = 1;

    while (true) {
        while (d == 1) {
            x = g(x);
            y = g(g(y));
            d = gcd(abs(x - y), n);
        }
        if (d != n) {
            res.first = d;
            res.second = n / d;
            break;
        }
        y = x = rand() % (n - 2) + 2;
        d = 1;
    }

    return res;
}

// prime decomposition for m <= 10^18
unordered_map<long, int> decomposition(long m) {
    unordered_map<long, int> pf;
    for (int i = 0; i < NP && primes[i] * primes[i] <= m; ++i) {
        long p = primes[i];
        while (m % p == 0) {
            pf[p]++;
            m /= p;
        }
    }

    if (m <= N * N) {
        if (m != 1) pf[m]++;
    } else {
        if (miller_rabin(m)) {
            pf[m]++;
        } else {
            auto pl = pollard_rho(m);
            pf[pl.first] = 1;
            pf[pl.second] = 1;
        }
    }

    return pf;
}

long value(const unordered_map<long, int> &mf) {
    long res = 1;
    for (auto &e : mf) {
        res *= fast_pow(e.first, e.second);
    }
    return res;
}

unordered_map<long, int> phi(const unordered_map<long, int> &mf) {
    auto mf_ = mf;

    for (auto &e : mf) {
        // assert(e.second > 0);
        auto p = e.first;
        mf_[p]--;
        auto pf = decomposition(p - 1);
        for (auto &pe : pf) {
            mf_[pe.first] += pe.second;
        }

        if (mf_[p] == 0) mf_.erase(p);
    }

    return mf_;
}
