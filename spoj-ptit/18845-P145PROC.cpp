#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
std::set<int> st;
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int t;
  for (int i = 1; i <= 10; ++i) {
    scanf("%d", &t);
    st.insert(t % 42);
  }
  printf("%d", st.size());
} 