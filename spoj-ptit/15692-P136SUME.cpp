SPOJ submission 11202760 (C++ 4.3.2) plaintext list. Status: AC, problem P136SUME, contest PTIT. By enrevol (What Does The Fox Say?), 2014-03-07 13:28:53.
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
typedef std::pair<int, int> p2;
 
std::map<int, p2> m;
int a[1010];
 
bool ff(int a, int b) {
  if (m[a].second == m[b].second)
    return m[a].first < m[b].first;
  return m[a].second > m[b].second;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, c;
  scanf("%d %d", &n, &c);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    if (m.find(a[i]) == m.end())
      m[a[i]].first = i;
    ++m[a[i]].second;
  }
  std::sort(a + 1, a + n + 1, ff);
  for (int i = 1; i <= n; ++i)
    printf("%d ", a[i]);
} 