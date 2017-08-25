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

int main(){
    vector<long> primes(1, 2);
    int i = 3;
    while (primes.size() < 1e4) {
        bool is_prime = true;
        for (auto p : primes) {
            if (i % p == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) primes.push_back(i);
        ++ i;
    }

    int t;
    cin >> t;

    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;

        cout << primes[n - 1] << endl;
    }
    return 0;
}

