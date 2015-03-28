SPOJ submission 11158882 (C++ 4.3.2) plaintext list. Status: AC, problem P144PROF, contest ACMPTIT. By enrevol (What Does The Fox Say?), 2014-03-01 05:02:30.
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
typedef std::pair<int, int> p2;
 
std::vector<p2> v[26];
char s[555];
 
int d(p2 a, p2 b) {
  if (a.first > b.first) std::swap(a, b);
  int res = b.first - a.first;
  if (a.second > b.second) res += a.second - b.second;
  else res = std::max(res, b.second - a.second);
  return res;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  while (1) {
    scanf("%d", &n);
    if (n == 0) break;
    scanf("%s", s + 1);
    for (int i = 0; i < 26; ++i)
      v[i].clear();
    int x = 1;
    int y = 1;
    int r = 1;
    for (int i = 1; s[i]; ++i) {
      v[s[i] - 'a'].push_back(p2(x, y));
      ++x;
      if (x > r) {
        x = 1;
        ++y;
        ++r;
      }
    }
    int cnt = 0;
    for (int i = 0; i < 26; ++i) {
      bool f = false;
      for (size_t x = 0; x < v[i].size() && !f; ++x)
        for (size_t y = x + 1; y < v[i].size() && !f; ++y)
          for (size_t z = y + 1; z < v[i].size() && !f; ++z) {
            int o = d(v[i][x], v[i][y]);
            int p = d(v[i][y], v[i][z]);
            int q = d(v[i][z], v[i][x]);
            f = o == p && p == q;
          }
      if (f) {
        putchar(i + 'a');
        ++cnt;
      }
    }
    if (cnt) putchar('\n');
    else puts("LOOOOOOOOSER!");
  }
} 