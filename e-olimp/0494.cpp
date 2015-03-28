#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
string s;
int main() {
 getline(cin, s, '\n');
 int ans = 0;
 for (int i = 0; i < s.length(); ++i)
   if (s[i] == 'A' ||
       s[i] == 'E' ||
       s[i] == 'I' ||
       s[i] == 'O' ||
       s[i] == 'U' ||
       s[i] == 'Y') ans++;
 cout << ans << '\n';
}