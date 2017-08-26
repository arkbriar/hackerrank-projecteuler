#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int tri[15][15];
int dp[15][15];

int main() {
    int t;
    cin >> t;
    while (t -- ) {
        int n;
        cin >> n;

        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j <= i; ++ j) {
                cin >> tri[i][j];
            }
        }

        dp[0][0]= tri[0][0];

        for (int i = 1; i < n; ++ i) {
            for (int j = 0; j <= i; ++ j) {
                if (j == 0) dp[i][j] = dp[i - 1][j] + tri[i][j];
                else if (j == i) dp[i][j] = dp[i - 1][j - 1] + tri[i][j];
                else dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + tri[i][j];
            }
        }

        int res = 0;
        for (int i = 0; i < n; ++ i) {
            res = max(res, dp[n - 1][i]);
        }
        cout << res << endl;
    }
    return 0;
}
