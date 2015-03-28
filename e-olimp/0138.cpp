#include <iostream>
using namespace std;
int ss[] = { 10, 20, 50, 100, 200, 500 };
int main() {
 int n, ans = 0;
 cin >> n;
 for (int i = 5; i >= 0; --i) {
   ans += n / ss[i];
   n %= ss[i];
 }
 if (n) ans = -1;
 cout << ans << '\n';
}