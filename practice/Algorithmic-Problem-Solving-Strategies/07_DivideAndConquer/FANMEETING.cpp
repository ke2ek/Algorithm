// https://algospot.com/judge/problem/read/FANMEETING
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Returns the result of multiplying two large numbers.
// For instance, [3, 2, 1] means 123.
vector<int> multiply(const vector<int>& a, const vector<int>& b) {
    vector<int> c(a.size() + b.size() + 1, 0);
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b.size(); j++)
            c[i+j] += a[i] * b[j];
    // except normalization
    return c;
}

// a += b * (10^k);
void addTo(vector<int>& a, const vector<int>& b, int k) {
    a.resize(max(a.size(), b.size() + k));
    for (int i = 0; i < b.size(); i++)
        a[i+k] += b[i];
}

// a -= b; (a >= b)
void subFrom(vector<int>& a, const vector<int>& b) {
    a.resize(max(a.size(), b.size()) + 1);
    for (int i = 0; i < b.size(); i++)
        a[i] -= b[i];
}

// Return the multiplication of two big integers.
vector<int> karatsuba(const vector<int>& a, const vector<int>& b)
{
    int an = a.size(), bn = b.size();
    // Assume that the length of a is not shorter than the length of b.
    if (an < bn) return karatsuba(b, a);
    // base case: a or b is empty.
    if (an == 0 || bn == 0) return vector<int> ();
    // base case: the length of a is short.
    if (an <= 50) return multiply(a, b); // O(n^2)
    int half = an / 2;
    vector<int> a0(a.begin(), a.begin() + half);
    vector<int> a1(a.begin() + half, a.end());
    vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
    vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());

    // z2 = a1 * b1
    vector<int> z2 = karatsuba(a1, b1);
    // z0 = a0 * b0
    vector<int> z0 = karatsuba(a0, b0);
    addTo(a0, a1, 0); // a0 = a0 + a1
    addTo(b0, b1, 0); // b0 = b0 + b1
    // z1 = (a0 * b0) - z0 - z2
    vector<int> z1 = karatsuba(a0, b0);
    subFrom(z1, z0);
    subFrom(z1, z2);
    // ret = z0 + z1 * 10^half + z2 * 10^(half*2)
    vector<int> ret;
    addTo(ret, z0, 0);
    addTo(ret, z1, half);
    addTo(ret, z2, half + half);
    return ret;
}

void solve() {
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.size(), m = s2.size();
    vector<int> members(n), fans(m);
    for (int i = 0; i < n; i++) members[i] = (s1[i] == 'M');
    for (int i = 0; i < m; i++) fans[m-i-1] = (s2[i] == 'M');
    vector<int> C = karatsuba(members, fans);
    int allHugs = 0;
    for (int i = n - 1; i < m; i++)
        if (C[i] == 0)
            allHugs++;
    cout << allHugs << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}

