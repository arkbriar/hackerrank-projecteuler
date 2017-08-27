#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const long MOD = 1e9 + 7;

long mulmod(long a, long b, long m) {
    // add this to avoid SIGFPE when m is two small for ab
    // so that ab/m can not be stored in 64-bit reg
    a %= m; b %= m;
    long res;
    asm("mulq %2; divq %3" : "=d"(res), "+a"(a) : "S"(b), "c"(m));
    return res;
}

int main() {
    int t;
    cin >> t;

    while (t --) {
        long n;
        cin >> n;

        n /= 2;

        // let n = floor(N / 2), sum = 2n^2 + 6n + 8n(n + 1)(2n + 1)/3 + 1

        long res = 1 + 2 * mulmod(n, n, MOD) + (6 * n) % MOD;

        long a = n, b = n + 1, c = 2 * n + 1;
        if (c % 3 == 0) c /= 3;
        else if (b % 3 == 0) b /= 3;
        else a /= 3;

        res += mulmod(mulmod(a, b, MOD), c, MOD) * 8;

        cout << res % MOD << endl;
    }
    return 0;
}

