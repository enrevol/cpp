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
 
#define m2 std::make_pair
#define m3(a, b, c) m2(m2(a, b), c)
 
typedef std::pair<int, int> p2;
typedef std::pair<p2, int> p3;
 
struct ff {
  bool operator() (const p3& a, const p3& b) {
    return a.first < b.first;
  }
};
 
typedef std::set<p3, ff>::iterator s_p3;
 
std::set<p3, ff> st;
int x_1[1010], y_1[1010], x_2[1010], y_2[1010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n;
  scanf("%d", &n);  
  for (int i = 1; i <= n; ++i)
    scanf("%d %d", x_1 + i, y_1 + i);
  for (int i = 1; i <= n; ++i)
    scanf("%d %d", x_2 + i, y_2 + i);
  for (int i = 1; i <= n; ++i) {
    st.clear();
    for (int j = i + 1; j <= n; ++j) {
      int a = y_1[j] - y_1[i];
      int b = x_1[i] - x_1[j];
      int g = std::__gcd(a, b);
      a /= g;
      b /= g;
      if (a < 0) {
        a = -a;
        b = -b;
      }      
      st.insert(m3(a, b, j));
    }
    for (int j = 1; j <= n; ++j) {
      int a = y_2[j] - y_1[i];
      int b = x_1[i] - x_2[j];
      int g = std::__gcd(a, b);
      a /= g;
      b /= g;
      if (a < 0) {
        a = -a;
        b = -b;
      }      
      p3 t = m3(a, b, j);
      s_p3 it = st.find(t);
      if (it != st.end()) {
        printf("%d %d %d", i, j + n, (*it).second);
        return 0;
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    st.clear();
    for (int j = i + 1; j <= n; ++j) {
      int a = y_2[j] - y_2[i];
      int b = x_2[i] - x_2[j];
      int g = std::__gcd(a, b);
      a /= g;
      b /= g;
      if (a < 0) {
        a = -a;
        b = -b;
      }      
      st.insert(m3(a, b, j));
    }
    for (int j = 1; j <= n; ++j) {
      int a = y_1[j] - y_2[i];
      int b = x_2[i] - x_1[j];
      int g = std::__gcd(a, b);
      a /= g;
      b /= g;
      if (a < 0) {
        a = -a;
        b = -b;
      }      
      p3 t = m3(a, b, j);
      s_p3 it = st.find(t);
      if (it != st.end()) {
        printf("%d %d %d", i + n, j, (*it).second + n);
        return 0;
      }
    }
  }
  puts("-1");
}