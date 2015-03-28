#include <iostream>
using namespace std;
int main() {
 int n, ans = 0;
 cin >> n;
 if (n == 0) ans = 1;
 while (n) {
   ans++;
   n /= 10;
 }  
 cout << ans << '\n';
}