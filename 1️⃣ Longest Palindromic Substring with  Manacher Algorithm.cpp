#include <bits/stdc++.h>
using namespace std;


string preprocess(const string &s) {
    string t = "#";
    for (char c : s) {
        t += c;
        t += "#";
    }
    return t;
}

string longestPalindrome(string s) {
    string t = preprocess(s);
    int n = t.size();
    vector<int> p(n, 0);
    int center = 0, right = 0;
    int maxLen = 0, centerIndex = 0;

    for (int i = 0; i < n; i++) {
        int mirror = 2 * center - i;

        if (i < right)
            p[i] = min(right - i, p[mirror]);

        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n && t[i - p[i] - 1] == t[i + p[i] + 1])
            p[i]++;

    
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

      
        if (p[i] > maxLen) {
            maxLen = p[i];
            centerIndex = i;
        }
    }

    int start = (centerIndex - maxLen) / 2;
    return s.substr(start, maxLen);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    cout << longestPalindrome(s) << "\n";
    return 0;
}
