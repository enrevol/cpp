#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int r;
  scanf("%d", &r);
  printf("%.16lf\n%.16lf", 3.14159265358979 * r * r, 2.f * r * r);
} 