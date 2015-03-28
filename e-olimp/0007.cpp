#include <iostream>
#include <string>
using namespace std;
string str[2005];
string s1[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
string s2[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
string s3[] = {"", "C", "CC", "CCC", "CD", "D", "DX", "DXX", "DXXX", "CM"};
string s4[] = {"", "M", "MM"};
int main() {
 for (int i = 1; i <= 2000; ++i) {
   str[i] = "";
   str[i] += s4[i / 1000];
   str[i] += s3[(i % 1000) / 100];
   str[i] += s2[(i % 100) / 10];
   str[i] += s1[i % 10];
 }  
 string s;
 cin >> s;
 s += '+';
 string t = "";
 int ans = 0;
 for (int i = 0; i < s.length(); ++i) {    
   if (s[i] == '+') {
     for (int j = 1; j <= 2000; ++j)
       if (t == str[j]) ans += j;
     t = "";
   } else {
     t += s[i];
   }
 }
 cout << str[ans] << '\n';
}