#include <bits/stdc++.h>
using namespace std;

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    
    int n = s1.size();
    int m = s2.size();
    
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    int maxLen = 0;
    int endPos = -1;  
    
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                if(dp[i][j] > maxLen) {
                    maxLen = dp[i][j];
                    endPos = i-1; 
                }
            } else {
                dp[i][j] = 0; 
            }
        }
    }
    
    if(maxLen == 0) {
        cout << "No common substring\n";
    } else {
        cout << "Longest common substring length: " << maxLen << "\n";
        cout << "Substring: " << s1.substr(endPos - maxLen + 1, maxLen) << "\n";
    }
}
