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

const int N = 100010;

std::deque<std::string> deq;
std::map<std::string, int> mymap;
std::map<int, int> rmq;
std::set<std::string> myset[N];

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int tt;
  std::cin >> tt;
  for (int tn = 1; tn <= tt; ++tn) {
    int n, k;
    std::cin >> n >> k;
    deq.clear();
    mymap.clear();
    rmq.clear();
    for (int i = 1; i <= n; ++i) {
      myset[i].clear();
    }
    std::cout << "Case " << tn << ":\n";
    while (n--) {
      std::string s;
      std::cin >> s;
      deq.push_back(s);
      int p = ++mymap[s];
      if (p > 1) {
        myset[p - 1].erase(s);
        --rmq[p - 1];
        if (rmq[p - 1] == 0) rmq.erase(p - 1);
      }
      myset[p].insert(s);
      ++rmq[p];
      if (deq.size() > k) {
        std::string t = deq.front();
        deq.pop_front();
        p = --mymap[t];
        myset[p + 1].erase(t);
        if (p > 0) {
          myset[p].insert(t);
          ++rmq[p];
        }
        if (mymap[t] == 0) mymap.erase(t);
        --rmq[p + 1];
        if (rmq[p + 1] == 0) rmq.erase(p + 1);
      }
      int v = rmq.rbegin()->first;
      std::cout << *myset[v].begin() << ' ' << v << '\n';
    }
  }
}