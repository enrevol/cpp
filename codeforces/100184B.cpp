// 2013 ACM-ICPC Ukraine, Round 1
// B - Watson's memory

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

char s[222];

int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  scanf("%s", s + 1);
  int sum = 0;
  for (int i = 1; s[i]; ++i)
    sum += s[i] - '0';
  if (sum % 3 == 0) printf("yes");
  else printf("no");
}