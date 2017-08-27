#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;

const int N = 8;
const int C[N] = {1, 2, 5, 10, 20, 50, 100, 200};

long dp[100001][N + 1];

int solve(int n, int i) {
    if (dp[n][i] >= 0) return dp[n][i];

    // This is because dp[n][i] = sum(dp[n % C[i - 1] + k * C[i - 1]][i - 1]), k <= n / C[i - 1],
    // then we can deduce that dp[n][i] = dp[n - C[i - 1]][i] + dp[n][i - 1];
    // Or it can be understood as take C[i - 1] and count the left then add the size of not using C[i - 1].
    if (n >= C[i - 1]) dp[n][i] = solve(n - C[i - 1], i) + solve(n, i - 1);
    else dp[n][i] = solve(n , i - 1);
    dp[n][i] %= MOD;

    return dp[n][i];
}

int main() {
    int t;
    cin >> t;

    // fill all we know and easy to cal
    fill_n((long *)dp, 100001 * (N + 1), -1);
    fill_n(dp[0], N + 1, 1);
    for (int i = 1; i <= 100000; ++i) {
        dp[i][0] = 0;
        dp[i][1] = 1;
    }
    for (int i = 1; i <= 100000; ++ i) {
        dp[i][2] = i / 2 + 1;
    }

    while (t--) {
        int n;
        cin >> n;
        cout << solve(n, N) << endl;
    }
    return 0;
}
