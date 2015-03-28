#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
const int mod = 1000000007;
 
int main() {
  //freopen("input.txt", "r", stdin);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    int val_1 = (1ll * n * (n - 1)) % mod;
    int val_2 = (1ll * (n - 2) * (n - 3)) % mod;
    int ans = (1ll * val_1 * val_2) % mod;    
    printf("%d\n", (41666667ll * ans) % mod);
  }
} 