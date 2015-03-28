#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

int main() {
  std::ifstream fin("fraud.in");
  std::ofstream fout("fraud.out");
  int n;
  std::string s;
  fin >> s >> n;
  std::vector<std::string> ans;
  for (int i = 1; i <= n; ++i) {
    std::string t;
    fin >> t;
    int f = 1;
    for (int i = 0; i < 9 && f; ++i)
      if (s[i] != '*' && s[i] != t[i]) f = 0;
    if (f) ans.push_back(t);
  }
  fout << ans.size() << '\n';
  for (auto a : ans) fout << a << '\n';
}