#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#define pSS pair<string, string>
#define pCC pair<char, char>
typedef long long LL;
using namespace std;
map<pSS, int> ms;
map<pCC, int> mc[100005];
int cnt[100005];
int main() {
  freopen("GENEMAP.INP", "r", stdin);
  freopen("GENEMAP.OUT", "w", stdout);
  ios::sync_with_stdio(0);
  int n, k;
  cin >> n >> k;
  string s;
  int sz, t, d = 0;
  pSS ps;
  pCC pc;
  for (int i = 0; i < n; ++i) {
    cin >> s;
    sz = s.length();
    if (sz < k) continue;
    ps = make_pair(s.substr(0, k), s.substr(sz - k, k));
    if (sz == k) {
      pc = make_pair('1', '1');
    } else {
      pc = make_pair(s[k], s[sz - k - 1]);
    }
    t = ms[ps];
    if (!t) {
      d++;
      ms[ps] = d;
      t = d;
    }
    mc[t][pc]++;
    cnt[t]++;
  }
  LL ans = 0, tot;
  for (int i = 1; i <= d; ++i) {
    for (map<pCC, int>::iterator ii = mc[i].begin(); ii != mc[i].end(); ++ii) {
      tot = ii->second;
      if (ii->first.first == '1') {
        tot *= cnt[i] - 1;
      } else {
        tot *= cnt[i] - tot;
      }
      ans += tot;
    }
  }
  cout << (ans / 2) % 1000000007;
}