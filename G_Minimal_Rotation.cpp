#include<bits/stdc++.h>
#define int long long int
#define ll long long 
//#define mod 1000000007
#define int_max 1e18
#define inf 10000001
#define hae printf("YES\n")
#define na printf("NO\n")

using namespace std;
int ts=1;


const int mod1 = 911382323, mod2 = 972663749, b1 = 137, b2 = 139;
const int mxN = 5e6 + 10; 
int pow_b1[mxN], pow_b2[mxN], invpow_b1[mxN], invpow_b2[mxN];

int power(int a, int b, int mod) {
	int ans = 1;
	while (b) {
		if (b & 1)
			ans = (ans * 1LL * a) % mod;
		a = (a * 1LL * a) % mod;
		b >>= 1;
	}
	return ans;
}

void pre() {
	pow_b1[0] = pow_b2[0] = 1;
	for (int i = 1; i < mxN; ++i) {
		pow_b1[i] = 1LL * pow_b1[i - 1] * b1 % mod1;
		pow_b2[i] = 1LL * pow_b2[i - 1] * b2 % mod2;
	}
	invpow_b1[mxN - 1] = power(pow_b1[mxN - 1], mod1 - 2, mod1);
	invpow_b2[mxN - 1] = power(pow_b2[mxN - 1], mod2 - 2, mod2);
	for (int i = mxN - 2; i >= 0; --i) {
		invpow_b1[i] = (1LL * invpow_b1[i + 1] * b1) % mod1;
		invpow_b2[i] = (1LL * invpow_b2[i + 1] * b2) % mod2;
	}
}

pair<int, int> getHash(string &str) {
	int hsh1 = 0, hsh2 = 0, sz = str.size();
	for (int i = 0; i < sz; ++i)
		hsh1 = (hsh1 + 1LL * str[i] * pow_b1[i] % mod1) % mod1;
	for (int i = 0; i < sz; ++i)
		hsh2 = (hsh2 + 1LL * str[i] * pow_b2[i] % mod2) % mod2;
	return {hsh1, hsh2};
}

vector<pair<int, int>> getPrefixHash(string &str) {
	int sz = str.size();
	vector<pair<int, int>> ret(sz);
	for (int i = 0; i < sz; ++i) {
		if (i == 0) {
			ret[i].first = (1LL * str[i] * pow_b1[i] % mod1) % mod1;
			ret[i].second = (1LL * str[i] * pow_b2[i] % mod2) % mod2;
		} else {
			ret[i].first =
			    (ret[i - 1].first + 1LL * str[i] * pow_b1[i] % mod1) % mod1;
			ret[i].second =
			    (ret[i - 1].second + 1LL * str[i] * pow_b2[i] % mod2) % mod2;
		}
	}
	return ret;
}

pair<int, int> getSubstrHash(int l, int r, vector<pair<int, int>> &prefixHash) {
	if (l == 0)
		return prefixHash[r];
	else {
		pair<int, int> ret;
		ret.first = (prefixHash[r].first - prefixHash[l - 1].first + mod1) % mod1;
		ret.first = (1LL * ret.first * invpow_b1[l]) % mod1;
		ret.second =
		    (prefixHash[r].second - prefixHash[l - 1].second + mod2) % mod2;
		ret.second = (1LL * ret.second * invpow_b2[l]) % mod2;
		return ret;
	}
}

void solve(){
    string s;
    cin >> s;
    int n = s.size();
    string t = s + s;               
    auto fg = getPrefixHash(t);    
    int best = 0; 
    for(int i = 1; i < n; i++){
        int l = 0, r = n;          
        while(l < r){
            int m = (l + r)/2;
            auto h1 = getSubstrHash(best, best + m, fg);
            auto h2 = getSubstrHash(i, i + m, fg);
            if(h1 == h2) l = m+1;  
            else r = m;            
        }
        if(l < n && t[i+l] < t[best+l])
            best = i;              
    }

    string ans = t.substr(best, n);
    cout << ans << endl;
}



int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    pre();
    ll t=1;
   // cin >> t;
    while(t--){
        solve();
    }
}