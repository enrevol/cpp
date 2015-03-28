#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

const int N = 1010;

bool sv[N];

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, k;
  while (~scanf("%d %d", &n, &k)) {
    memset(sv, 0, sizeof(sv));
    int f = 1;
    for (int i = 2; i <= n && f; ++i)
      if (!sv[i]) {
        --k;
        if (k == 0) {
          printf("%d\n", i);
          f = 0;
        }
        for (int j = i * i; j <= n && f; j += i)
          if (!sv[j]) {
            sv[j] = 1;
            --k;
            //fprintf(stderr, "%d\n", j);
            if (k == 0) {
              printf("%d\n", j);
              f = 0;
            }
          }
      }
  }
}

