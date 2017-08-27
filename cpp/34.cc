#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int fact[10] = {1};

int sum_of_fact(int x) {
    int res = 0;
    while (x) {
        res += fact[x % 10];
        x /= 10;
    }
    return res;
}

int main() {
    for (int i = 1; i < 10; ++i) {
        fact[i] = fact[i - 1] * i;
    }

    int n;
    cin >> n;

    long res = 0;
    for (int i = 19; i < n; ++i) {
        if (sum_of_fact(i) % i == 0) {
            res += i;
        }
    }
    cout << res << endl;
    return 0;
}
