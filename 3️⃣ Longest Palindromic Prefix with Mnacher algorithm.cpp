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

void longestPalindrome(string s) {
    string t = preprocess(s);
    int n = t.size();
    vector<int> p(n, 0);
    int center = 0, right = 0;
    int maxLen1 = 0, centerIndex = 0,maxLen2=0;

    int total=0;

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

        if(i-p[i]==0) maxLen1 = max(maxLen1, p[i]);
        if(i+p[i]==n-1) maxLen2 = max(maxLen2, p[i]);
    }

       string prefix=s.substr(0, maxLen1);
       string suff=s.substr(s.size()-maxLen2, maxLen2);


       cout<<prefix<<" "<<suff<<endl;
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    longestPalindrome(s);

    return 0;
}