#include <bits/stdc++.h>
using namespace std;


int booth(string s) {
    s += s;
    int n = s.size();
    vector<int> f(n, -1);
    int k = 0;
    for (int j = 1; j < n; j++) {
        int i = f[j - k - 1];
        while (i != -1 && s[j] != s[k + i + 1]) {
            if (s[j] < s[k + i + 1])
                k = j - i - 1;
            i = f[i];
        }
        if (i == -1 && s[j] != s[k]) {
            if (s[j] < s[k])
                k = j;
            f[j - k] = -1;
        } else {
            f[j - k] = i + 1;
        }
    }
    return k; 
}

int main() {
    string s;
    cin >> s;
    int idx = booth(s);
    string ans = s.substr(idx) + s.substr(0, idx);
    cout << ans << endl;
}
