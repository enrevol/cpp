#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
std::vector<char> v;
char s[111], g[11][1010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  int tt, n_case = 0;
  scanf("%d", &tt);
  while (tt--) {
    scanf("%s", s + 1);
    int sz = strlen(s + 1);
    char last = s[1];
    v.clear();
    v.push_back(last);
    for (int i = 2; i <= sz; ++i) {      
      while (last + 1 < s[i]) {
        ++last;
        v.push_back(last);
      }
      while (last - 1 > s[i]) {
        --last;
        v.push_back(last);
      }
      v.push_back(s[i]);
      last = s[i];
    }
    memset(g, 0, sizeof(g));
    int mx = 1;
    for (int j = 0; j < v.size(); ++j) {
      for (int i = 1; i <= v[j] - '0'; ++i)
        g[i][j] = '+';
      for (int i = v[j] - '0' + 1; i <= 10; ++i)
        g[i][j] = '*';
      mx = std::max(mx, v[j] - '0');      
    }
    for (int  i = mx; i >= 1; --i)
      puts(g[i]);
  }
}