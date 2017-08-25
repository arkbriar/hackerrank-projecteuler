#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

vector<int> primes;

int main() {
    int t;
    cin >> t;

    for (int i = 2; i < 40; ++i) {
        if (primes.empty())
            primes.push_back(i);
        else {
            bool is_prime = true;
            for (auto p : primes) {
                if (i % p == 0) {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime) primes.push_back(i);
        }
    }

    for (int a0 = 0; a0 < t; a0++) {
        int n;
        cin >> n;

        unordered_map<int, long> par;

        for (int i = 2; i <= n; ++i) {
            int i_ = i;
            for (auto p : primes) {
                long c = 1;
                while (i_ % p == 0) {
                    i_ /= p;
                    c *= p;
                }
                par[p] = max(par[p], c);
            }
        }

        long res = 1;
        for (auto &e : par) {
            res *= e.second;
        }
        cout << res << endl;
    }
    return 0;
}
