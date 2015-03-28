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
typedef std::set<int>::iterator s_i;
 
struct ss {
  int left, top, right, bottom;
} fr[255];
 
std::set<int> pa[255];
std::vector<int> v[33], v_t[255], ch[255], v_have;
char s[55][55], ar[55];
int have[255], used[255];
 
void ff(const int& idx, const int& sz) {
  if (idx > sz ) {
    for (int i = 1; i <= sz; ++i)
      printf("%c", ar[i]);
    putchar('\n');
  } else {
    for (int i = 0; i < v_have.size(); ++i) {
      int e = v_have[i];
      if (!used[e]) {
        int f = 1;
        for (int j = 0; j < ch[e].size() && f; ++j)
          if (!used[ch[e][j]]) f = 0;
        if (f) {
          ar[idx] = e;
          used[e] = 1;
          ff(idx + 1, sz);
          used[e] = 0;
        }
      }
    }
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  for (int i = 'A'; i <= 'Z'; ++i) {
    fr[i].bottom = fr[i].right = 1;
    fr[i].top = fr[i].left = 33;
  }
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", s[i] + 1);
    for (int j = 1; j <= m; ++j)
      if (s[i][j] != '.') {
        char c = s[i][j];
        if (j < fr[c].left)   fr[c].left = j;
        if (j > fr[c].right)  fr[c].right = j;
        if (i < fr[c].top)    fr[c].top = i;
        if (i > fr[c].bottom) fr[c].bottom = i;
        have[c] = 1;
      }
  }
  for (int i = 'A'; i <= 'Z'; ++i) {
    if (have[i]) {
      for (int j = fr[i].top; j <= fr[i].bottom; ++j) {
        char a = s[j][fr[i].left];
        char b = s[j][fr[i].right];
        if (a != '.' && a != i) pa[i].insert(a);
        if (b != '.' && b != i) pa[i].insert(b);
      }
      for (int j = fr[i].left; j <= fr[i].right; ++j) {
        char a = s[fr[i].top][j];
        char b = s[fr[i].bottom][j];
        if (a != '.' && a != i) pa[i].insert(a);
        if (b != '.' && b != i) pa[i].insert(b);
      }
    }
  }
  for (int i = 'A'; i <= 'Z'; ++i)
    if (have[i])
      for (s_i it = pa[i].begin(); it != pa[i].end(); ++it)
        for (s_i jt = pa[*it].begin(); jt != pa[*it].end(); ++jt)
          v_t[i].push_back(*jt);
  for (int i = 'A'; i <= 'Z'; ++i) {
    for (int j = 0; j < v_t[i].size(); ++j)
      pa[i].erase(v_t[i][j]);
    for (s_i it = pa[i].begin(); it != pa[i].end(); ++it)
      ch[*it].push_back(i);
  }
  for (int i = 'A'; i <= 'Z'; ++i)
    if (have[i])
      v_have.push_back(i);
  int sz = 0;
  for (int i = 'A'; i <= 'Z'; ++i)
    sz += have[i];
  ff(1, sz);
} 