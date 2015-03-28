#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
typedef std::pair<int, int> p2;
 
std::set<std::string> st;
 
int main() {
  int tt;
  std::cin >> tt;
  std::cin.ignore(1);
  while (tt--) {
    st.clear();
    std::string s;
    std::getline(std::cin, s);
    std::stringstream ss(s);
    while (ss >> s) st.insert(s);
    std::cout << st.size() << '\n';
  }
} 