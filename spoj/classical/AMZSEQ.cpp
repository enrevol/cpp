#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
int a[1010][3];
 
int main() {
  //freopen("input.txt", "r", stdin);
  int n;
  scanf("%d", &n);
  a[1][0] = a[1][1] = a[1][2] = 1;
  for (int i = 2; i <= n; ++i) {
    a[i][0] = a[i - 1][0] + a[i - 1][1];
    a[i][1] = a[i - 1][0] + a[i - 1][1] + a[i - 1][2];
    a[i][2] = a[i - 1][1] + a[i - 1][2];
  }
  printf("%d", a[n][0] + a[n][1] + a[n][2]);
} 