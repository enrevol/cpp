#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
using namespace std;
map<string, int> m;
string ss[] = { "Re", "Pt", "Cc", "Ea", "Tb", "Cm", "Ex" };
int main() {
  string s;
  int cnt = 0;
  while (cin >> s) {
    m[s]++;
    cnt++;
  }
  for (int i = 0; i < 7; ++i) {
    float d = m[ss[i]];
    cout << ss[i] << ' ' << setprecision(0) << d << setprecision(2) << ' ' << fixed << d / cnt << '\n';
  }
  cout << "Total " << cnt << " 1.00\n";
}