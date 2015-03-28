#include <cstdio>
#include <cstring>
#include <deque>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
char s[101010];
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int k;
    scanf("%s %d", s + 1, &k);
    std::deque<p2> de;
    int sz = strlen(s + 1);
    int num = sz - k;
    int left = 1, right = sz - (num - 1), start = left;
    while (num) {
      for (int i = start; i <= right; ++i) {
        while (de.size() && de.back().first < s[i])
          de.pop_back();
        de.push_back(m2(s[i], i));
      }
      p2 t = de.front();
      putchar(t.first);
      while (de.size() && de.front().second <= t.second)
        de.pop_front();
      left = t.second + 1;
      ++right;
      --num;
      start = right;
    }
    putchar('\n');
  }
} 