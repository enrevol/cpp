#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pLL;
int main() {
  int n;
  cin >> n;
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j * j <= i; ++j)
      if (i % j == 0) ++ans;
  cout << ans;
} 