#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
 
std::vector<std::string> words[111];
std::map<std::string, int> all_words;
 
int main() {
  //freopen("input.txt", "r", stdin);
  int n;
  scanf("%d%*c", &n);
  std::string line;
  for (int i = 1; i <= n; ++i) {
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string s;
    while (ss >> s) {      
      words[i].push_back(s);
      ++all_words[s];
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    int score = 0;
    for (int j = 0; j < words[i].size(); ++j)
      if (all_words[words[i][j]] == 1) {
        int sz = words[i][j].size();
        if (sz <= 4) ++score;
        else if (sz == 5) score += 2;
        else if (sz == 6) score += 3;
        else if (sz == 7) score += 5;
        else score += 11;
      }
    if (score > ans) ans = score;    
  }
  printf("%d", ans);
} 