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

long fib[100];

int main(){
    int t;
    cin >> t;

    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < 100; ++ i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    for(int a0 = 0; a0 < t; a0++){
        long n;
        cin >> n;

        long res = 0;
        for (int i = 0 ; i < 100 && fib[i] <= n; i += 3) {
            res += fib[i];
        }
        cout << res << endl;
    }
    return 0;
}

