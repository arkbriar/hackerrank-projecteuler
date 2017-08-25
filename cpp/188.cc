#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <cstdlib>
#include <cstdint>
#include <climits>
#include <limits>
#include <cassert>

using namespace std;

const long N = 1e6;
const int NP = 78498;

bool is_prime[N + 1];
long primes[NP];

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

long gcd(long a, long b) {
    long t;
    while (b != 0) {
        t = a % b;
        a = b;
        b = t;
    }
    return a;
}

long _g(long x, long n) { return (mulmod(x, x, n) + 1) % n; }

unordered_map<long, int> pollard_rho(long n) {
    unordered_map<long, int> res;

    auto g = [&](long x) { return _g(x, n); };
    long x = 2, y = 2, d = 1;

    while (true) {
        while (d == 1) {
            x = g(x);
            y = g(g(y));
            d = gcd(abs(x - y), n);
        }
        if (d != n) {
            res[d]++;
            res[n / d]++;
            break;
        }
        y = x = rand() % (n - 2) + 2;
        d = 1;
    }

    return res;
}

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
            for (auto &e : pl) {
                pf[e.first] += e.second;
            }
        }
    }

    return pf;
}

// return LLONG_MAX for all tetration larger than it
long tetration_approxiamtion(long a, long b) {
    if (a == 1) return 1;

    if (b == 1)
        return a;
    else if (b == 2) {
        if (a < 16) return fast_pow(a, a);
        else return LLONG_MAX;
    } else if (b == 3) {
        if (a == 2) return 64;
        else if (a == 3) return 7625597484987;
        else return LLONG_MAX;
    } else if (b == 4) {
        if (a == 2) return 65536;
        else return LLONG_MAX;
    } else return LLONG_MAX;
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

long tetration(long a, long b, long m) {
    if (a == 1 || b == 1) return a % m;

    stack<unordered_map<long, int>> st;
    while (b > 1 && (st.empty() || value(st.top()) != 1)) {
        if (st.empty())
            st.push(phi(decomposition(m)));
        else {
            auto t = st.top();
            st.push(phi(t));
        }
        --b;
    }

    long res = 1;
    while (!st.empty()) {
        auto t = value(st.top());
        st.pop();

        res = fast_pow(a, res, t);
        auto ap = tetration_approxiamtion(a, b);
        if (ap >= t) res += t;
        ++b;
    }

    res = fast_pow(a, res, m);
    return res % m;
}

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

int main() {
    int q;
    cin >> q;

    fill_primes();

    srand(time(0));
    while (q--) {
        long a, b, m;
        cin >> a >> b >> m;
        cout << tetration(a, b, m) << endl;
    }
    return 0;
}
