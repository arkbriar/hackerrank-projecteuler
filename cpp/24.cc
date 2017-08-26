#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

const string S = "abcdefghijklm";

int table[14];

int main() {
    int t;
    cin >> t;

    table[0] = 1;
    for (int i = 1; i < 14; ++ i) {
        table[i] = table[i - 1] * i;
    }

    while (t --) {
        int n;
        cin >> n;
        n --;

        // construct the string
        vector<char> cs(S.begin(), S.end());
        string res;
        for (int i = 0; i < 13; ++ i) {
            auto j = n / table[12 - i];
            res.push_back(cs[j]);
            cs.erase(cs.begin() + j);
            n %= table[12 - i];
        }

        cout << res << endl;
    }
    return 0;
}

