#include <algorithm>
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
 
int cnt[26];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  for (std::cin >> tt; tt--; ) {
    std::string s;
    do {
      std::getline(std::cin, s);
    } while (s.size() == 0);
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < int(s.size()); ++i)
      if (s[i] != ' ') {
        assert('A' <= s[i] && s[i] <= 'Z');
        ++cnt[s[i] - 'A'];
      }
    int* pos = std::max_element(cnt, cnt + 26);
    int num = 0;
    for (int i = 0; i < 26; ++i)
      num += cnt[i] == *pos;
    if (num > 1) {
      std::cout << "NOT POSSIBLE";
    } else {
      int d = pos - cnt + 'A';
      if (d < 'E') d = d + 26 - 'E';
      else d = d - 'E';
      std::cout << d << ' ';
      for (int i = 0; i < int(s.size()); ++i) {
        char c = s[i];
        if (c != ' ') {
          c -= d;
          if (c < 'A') c += 26;
        }
        std::cout << c;
      }      
    }
    std::cout << '\n';
  }
}