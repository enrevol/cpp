#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
typedef long long LL;
using namespace std;
vector<int> vec;
int main() {
  int sum = 0;
  for (int i = 1; i <= 50000; ++i) {
    sum += i;
    int sq = sqrt(sum + 1);
    if (sq * sq == sum + 1) {
      vec.push_back(sum + 1);
    }
  }
  int a, b, nCase = 0;
  while (cin >> a >> b) {
    if (a == 0 && b == 0) break;
    int ans = 0;
    for (int i = 0; i < vec.size(); ++i) {
      if (a < vec[i] && vec[i] < b) ans++;
    }    
    cout << "Case " << ++nCase << ": " << ans << '\n';
  }
}