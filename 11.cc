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

int main() {
    vector<vector<int> > grid(23, vector<int>(26));
    for (int i = 0; i < 20; ++i) {
        for (int j = 3; j < 23; ++j) {
            scanf("%d", &grid[i][j]);
        }
    }

    int res = 0;
    for (int i = 0; i < 20; ++i) {
        for (int j = 3; j < 23; ++j) {
            res = max(res, grid[i][j] * grid[i][j + 1] * grid[i][j + 2] * grid[i][j + 3]);
            res = max(res, grid[i][j] * grid[i + 1][j] * grid[i + 2][j] * grid[i + 3][j]);
            res =
                max(res, grid[i][j] * grid[i + 1][j + 1] * grid[i + 2][j + 2] * grid[i + 3][j + 3]);
            res =
                max(res, grid[i][j] * grid[i + 1][j - 1] * grid[i + 2][j - 2] * grid[i + 3][j - 3]);
        }
    }
    printf("%d\n", res);

    return 0;
}
