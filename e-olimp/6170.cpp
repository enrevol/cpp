#include <algorithm>
#include <iostream>
using namespace std;
struct ss {
 int a, b, c;
} s[1005];
int func(const ss& a, const ss& b) {
 if (a.c != b.c) return a.c > b.c;
 return a.b > b.b;
}
int a[1005];
int main() {
 int n, ans = 0;
 cin >> n;  
 for (int i = 0; i < n; ++i) {
   cin >> s[i].a >> s[i].b >> s[i].c;
   ans += s[i].b * s[i].c;
 }
 sort(s, s + n, func);
 //for (int i = 0; i < n; ++i) cout << s[i].a << ' ' << s[i].b << ' ' << s[i].c << '\n';
 for (int i = 0; i < n; ++i) {
   int t = -1;
   for (int j = 0; j < n; ++j) {
     if (!a[j]) {
       if (t == -1 || s[j].a > s[t].a) {
         if (s[j].a < s[i].b) {
           t = j;
         }
       }
     }
   }    
   if (t != -1) {
     a[t] = 1;
     ans -= s[t].a * s[i].c;
   }
 }
 cout << ans << '\n';
}