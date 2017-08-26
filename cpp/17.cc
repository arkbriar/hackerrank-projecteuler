#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <sstream>
using namespace std;

const unordered_map<long, string> mp = {
    {1, "One"},      {2, "Two"},        {3, "Three"},     {4, "Four"},        {5, "Five"},
    {6, "Six"},      {7, "Seven"},      {8, "Eight"},     {9, "Nine"},        {10, "Ten"},
    {11, "Eleven"},  {12, "Twelve"},    {13, "Thirteen"}, {14, "Fourteen"},   {15, "Fifteen"},
    {16, "Sixteen"}, {17, "Seventeen"}, {18, "Eighteen"}, {19, "Nineteen"},   {20, "Twenty"},
    {30, "Thirty"},  {40, "Forty"},     {50, "Fifty"},    {60, "Sixty"},      {70, "Seventy"},
    {80, "Eighty"},  {90, "Ninety"},    {100, "Hundred"}, {1000, "Thousand"}, {1000000, "Million"},
    {1e9, "Billion"}};

string write_in_thousand(int n) {
    int a = n / 100, b = n % 100;
    stringstream ss;
    if (a != 0) ss << mp.at(a) << " " << mp.at(100);
    if (b != 0) {
        if (!ss.str().empty()) ss << " ";

        if (b <= 20) {
            ss << mp.at(b);
        } else {
            ss << mp.at(b / 10 * 10);
            if (b % 10 != 0) ss << " " << mp.at(b % 10);
        }
    }
    return ss.str();
}

string write(long n) {
    if (n == 0) return "Zero";

    string res;
    long x = 1;
    while (n != 0) {
        auto part = write_in_thousand(n % 1000);
        if (!part.empty()) {
            if (x > 1) res = mp.at(x) + " " + res;
            res = part + " " + res;
        }

        n /= 1000;
        x *= 1000;
    }

    return res;
}

int main() {
    int t;
    cin >> t;
    long n;

    while (t--) {
        cin >> n;

        cout << write(n) << endl;
    }
    return 0;
}
