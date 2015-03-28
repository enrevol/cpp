#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
int arr[] = { 1, 4, 16, 121, 529, 4096, 17956, 139129, 609961, 4726276, 20720704, 160554241, 703893961 };
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  /*std::vector<int> v;
  for (int i = 1; i * i < 1000000000; ++i) {    
    int k = (i * i) - 1;
    int kk = k << 1;
    int sq = sqrt(kk);
    if (sq * (sq + 1) == kk)
      v.push_back(k + 1);
  }
  for (auto i : v)
    printf("%d\n", i);*/
  int a, b, n_case = 0;
  while (1) {
    scanf("%d %d", &a, &b);
    if (a == 0 && b == 0) break;
    int ans = 0;
    for (int i = 0; i < 13; ++i)
      ans += a < arr[i] && arr[i] < b;
    printf("Case %d: %d\n", ++n_case, ans);
  }
} 