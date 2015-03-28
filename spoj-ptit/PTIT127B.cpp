#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
char s[101010];
char a[50505];
char b[50505];
char used[101010];
std::vector<int> pos[26];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d %s", &n, s + 1);
  for (int i = 1; i <= n; ++i)
    pos[s[i] - 'a'].push_back(i);
  int an = 0;
  int bn = 0;
  for (int i = 1, j = n, k = 0; i <= n >> 1; ++i) {
    while (used[j]) --j;
    a[++an] = s[j];
    used[j] = 1;
    pos[s[j] - 'a'].pop_back();
    while (pos[k].size() == 0) ++k;
    b[++bn] = s[pos[k].back()];
    used[pos[k].back()] = 1;
    pos[k].pop_back();
  }
  puts(strcmp(b + 1, a + 1) < 0 ? "DA" : "NE");
  puts(b + 1);
}