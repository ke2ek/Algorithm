#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getPartialMatch(const string &needle) {
    int n = needle.length();
    vector<int> pi(n, 0);
    int begin = 1, matched = 0;
    pi.push_back(n);
    while (begin + matched < n) {
        if (matched < n && needle[begin+matched] == needle[matched]) {
            ++matched;
            pi[begin + matched - 1] = matched;
        } else {
            if (matched == 0) begin++;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return pi;
}

vector<int> kmpSearch(const string &haystack, const string &needle) {
    int h = haystack.length();
    int n = needle.length();
    vector<int> ret, pi = getPartialMatch(needle);
    int begin = 0, matched = 0;
    while (begin < h - n) {
        if (matched < n && haystack[begin+matched] == needle[matched]) {
            ++matched;
            if (matched == n) ret.push_back(begin);
        } else {
            if (matched == 0) begin++;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return ret;
}

// Another source same as above.
vector<int> kmpSearch2(const string &H, const string &N) {
    int n = H.size(), m = N.size();
    vector<int> ret;
    vector<int> pi = getPartialMatch(N);
    int matched = 0;
    for (int i = 0; i < n; i++) { // i == begin + matched
        while (matched > 0 && H[i] != N[matched])
            matched = pi[matched - 1];
        if (H[i] == N[matched]) {
            matched++;
            if (matched == m) {
                ret.push_back(i - m + 1); // begin
                matched = pi[matched - 1];
            }
        }
    }
    return ret;
}

int main() {
    string haystack, needle;
    cin >> haystack >> needle;
    // vector<int> result = kmpSearch(haystack, needle);
    vector<int> result = kmpSearch2(haystack, needle);
    cout << "'" << needle << "' starts at ";
    for (int i=0; i<result.size()-1; i++) {
        cout << result[i] << ", ";
    }
    cout << result[result.size()-1] << " in '" << haystack << "'." << endl;
    return 0;
}
