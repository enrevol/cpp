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
 
std::string arr[10101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  std::ios::sync_with_stdio(0);
  int tt;
  std::cin >> tt;
  while (tt--) {
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
      std::cin >> arr[i];
    std::sort(arr + 1, arr + n + 1);
    bool f = true;
    for (int i = 1; i < n && f; ++i)
      if (arr[i].size() <= arr[i + 1].size())
        if (arr[i] == arr[i + 1].substr(0, arr[i].size()))
          f = false;
    if (f) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }
}