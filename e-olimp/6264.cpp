#include <iostream>
#include <string>
typedef long long LL;
using namespace std;
int main() {
 int n;
 string str;
 cin >> n >> str;
 int r = n, k = 0, p = 0;
 LL ans = 0, s = 0;
 for (int i = 0; i < str.length(); ++i) {
   if (str[i] == '1') {      
     if (k) {
       k--;
       s++;
     } else if (r) {
       r--;
       s++;
     } else if (p) {
       p--;        
       k++;        
     } 
   } else {
     if (r >= 2) {
       p++;
       r -= 2;
       s += 1;
     }
   }
   ans += s;
   //cout << ans << ' ' << s << ' ' << r << ' ' << k << ' ' << p << '\n';
 }
 cout << ans << '\n';
}