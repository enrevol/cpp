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
 
typedef std::pair<int, int> p2;
 
std::vector<p2> e[11];
bool chosen[11];
int arr[11];
 
void dfs(const int& cur, const int& pre, const int& d) {
  if (d == 9) {
    for (int i = 0; i < d; ++i)
      printf("%d", arr[i]);
    putchar('\n');
  } else {
    for (size_t i = 0; i < e[cur].size(); ++i) {
      p2 t = e[cur][i];
      if (t.second != pre && !chosen[t.first]) {
        chosen[t.first] = true;
        arr[d] = t.second;
        dfs(t.second, cur, d + 1);
        chosen[t.first] = false;
      }
    }
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  e[1].push_back(std::make_pair(1, 2));
  e[1].push_back(std::make_pair(2, 3));
  e[1].push_back(std::make_pair(3, 5));
  e[2].push_back(std::make_pair(1, 1));
  e[2].push_back(std::make_pair(4, 3));
  e[2].push_back(std::make_pair(5, 5));
  e[3].push_back(std::make_pair(2, 1));
  e[3].push_back(std::make_pair(4, 2));
  e[3].push_back(std::make_pair(6, 4));
  e[3].push_back(std::make_pair(7, 5));
  e[4].push_back(std::make_pair(6, 3));
  e[4].push_back(std::make_pair(8, 5));
  e[5].push_back(std::make_pair(3, 1));
  e[5].push_back(std::make_pair(5, 2));
  e[5].push_back(std::make_pair(7, 3));
  e[5].push_back(std::make_pair(8, 4));
  arr[0] = 1;
  dfs(1, 0, 1);
}