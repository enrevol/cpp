#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
std::set<int> m, p;
 
int a[22];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int c, n;
  scanf("%d %d", &c, &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i);
  m.insert(0);
  for (int i = 1; i <= n; ++i) {
    p = m;
    for (std::set<int>::iterator it = p.begin(); it != p.end(); ++it)
      m.insert(*it + a[i]);
  }
  printf("%d", *(--m.upper_bound(c)));
}  