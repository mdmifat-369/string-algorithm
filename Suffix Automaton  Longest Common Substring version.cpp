#include <bits/stdc++.h>
using namespace std;

struct State {
    int len, link, first_pos;
    map<char,int> next;
};

vector<State> st;
int sz, last;

// Initialize Suffix Automaton
void sa_init(int maxLen) {
    st.clear();
    st.resize(2*maxLen);
    st[0].len = 0;
    st[0].link = -1;
    st[0].first_pos = -1;
    sz = 1;
    last = 0;
}

// Extend automaton with character c
void sa_extend(char c, int pos) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].first_pos = pos; // first occurrence of this state
    int p = last;
    while(p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if(p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if(st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            st[clone].first_pos = st[q].first_pos; // copy first_pos
            while(p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

// Find LCS with positions in both strings
tuple<int,int,int,int> longest_common_substring(const string &s2) {
    int v = 0, l = 0;
    int best = 0;
    int bestPosS2 = -1;
    int bestEndS1 = -1;

    for(int i = 0; i < (int)s2.size(); i++) {
        char c = s2[i];
        while(v != -1 && !st[v].next.count(c)) {
            v = st[v].link;
            if(v != -1) l = st[v].len;
        }
        if(v == -1) {
            v = 0;
            l = 0;
        } else {
            v = st[v].next[c];
            l++;
            if(l > best) {
                best = l;
                bestPosS2 = i;
                bestEndS1 = st[v].first_pos;
            }
        }
    }

    if(best == 0) return {0,0,0,0};

    int startS1 = bestEndS1 - best + 1;
    int startS2 = bestPosS2 - best + 1;

    return {startS1, best, startS2, best};
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;

    sa_init(s1.size());
    for(int i = 0; i < (int)s1.size(); i++) sa_extend(s1[i], i);

    auto [startS1, len, startS2, _] = longest_common_substring(s2);

    if(len == 0) {
        cout << "0 0 0 0\n";
    } else {
        cout << startS1 << " " << len << " " << startS2 << " " << len+startS2 << "\n";
    }

    return 0;
}
