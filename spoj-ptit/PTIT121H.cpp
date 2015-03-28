#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
char s[101010];
int arr[1515151];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int m, k;
  scanf("%d %d %s", &m, &k, s + 1);
  for (int i = 1; i <= m; ++i)
    arr[i] = i - 1;
  int sz = strlen(s + 1);
  for (int i = 1; i < sz; ++i) {
    if (s[i] == 'A') {
      arr[i + m] = arr[i];
    } else {
      arr[i + m] = arr[i + 1];
      arr[i + 1] = arr[i];
    }    
  }
  printf("%d %d %d", arr[sz + k - 1], arr[sz + k], arr[sz + k + 1]);
} 