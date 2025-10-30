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

vector<int>longestPalindrome(string s) {
    string t = preprocess(s);
    int n = t.size();
    vector<int> p(n, 0);
    int center = 0, right = 0;
    int maxLen= 0, centerIndex = 0;

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

    }

    return p;
}

bool isPalindromeQuery(int L, int R, const vector<int> &P) {
    int t_left = 2 * L + 1;     
    int t_right = 2 * R + 1;     

    int center = (t_left + t_right) / 2;               
    int radius_needed = (t_right - t_left) / 2 + 1; 

    return P[center] >= radius_needed;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    vector<int>p=longestPalindrome(s);

    int q;
    cin>>q;

    while(q--){
         int L,R;
         cin>>L>>R;

         if(isPalindromeQuery(L,R,p))cout<<"YES"<<endl;
         else cout<<"NO"<<endl;
    }

    return 0;
}