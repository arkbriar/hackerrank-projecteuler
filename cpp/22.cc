#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

long score(const string &s, long r) {
    return r * accumulate(s.begin(), s.end(), 0L,
                          [](const int &a, const char &c) { return a + c - 'A' + 1; });
}

int main() {
    int n;
    cin >> n;
    vector<string> names(n);
    for (int i = 0; i < n; ++i) {
        cin >> names[i];
    }

    sort(names.begin(), names.end());

    int q;
    cin >> q;
    while (q--) {
        string name;
        cin >> name;

        auto it = std::find(names.begin(), names.end(), name);
        cout << score(name, it - names.begin() + 1) << endl;
    }
    return 0;
}
