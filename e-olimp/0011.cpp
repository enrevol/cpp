#include <iostream>
#include <string>
using namespace std;
int main() {
 string s = "";
 int m, n, k;
 cin >> m >> n >> k;  
 if (k) {
   int d = 0;
   s += (m / n) + '0';
   s += '.';
   m %= n;
   while (d < k) {
     if (m != 0)
       m *= 10;
     s += (m / n) + '0';
     m %= n;
     d++;    
   }
   /*int b = s[s.length() - 1] >= '5';
   for (int i = s.length() - 2; i >= 0; --i) {
     if (s[i] != '.') {
       if (b) {        
         if (s[i] == '9') {
           s[i] = '0';
           b = 1;
         } else {
           s[i]++;
           b = 0;
         }
       } else {
         break;
       }
     }     
   }
   s[s.length() - 1] = 0;*/
   cout << s << '\n';
 } else {
   int ans = m / n;
   //if (m % n >= n / 2.f) ans++;
   cout << ans << '\n';
 }  
}