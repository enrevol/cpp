#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
bool b[3030303];
std::set<int> st[101010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, t;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &t);
    st[i].insert(t);
    b[t] = true;
    for (std::set<int>::iterator it = st[i - 1].begin(); it != st[i - 1].end(); ++it) {
      st[i].insert(*it | t);
      b[*it | t] = true;
    }
  }
  int ans = 0;
  for (int i = 0; i <= 3000000; ++i)
    ans += b[i];
  printf("%d", ans);
} 