#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
string s[33];
int main() {
 int n;
 cin >> n;
 for (int i = 0; i < 26; ++i) s[i] = i + 'a';
 for (int i = 0; i < n; ++i) {
   cout << 'a';
   for (int j = 0; j < n - i - 1; ++j) cout << ' ';
   for (int j = n - i - 1; j < n; ++j) cout << s[j - n + i + 1];
   cout << '\n';    
 }
}