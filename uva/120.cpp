#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
void flip(int a[], const int& idx) {
  for (int i = 0; i < (idx + 1) / 2; ++i)
    swap(a[i], a[idx - i]);
}
int main() {
  ios::sync_with_stdio(0);
  string s;
  while (getline(cin, s)) {
    stringstream ss(s);
    int a[35], d = 0, t;
    while (ss >> t) a[d++] = t;
    for (int i = 0; i < d; ++i)
      cout << a[i] << ' ';
    cout << '\n';
    for (int i = d - 1; i >= 0; --i) {
      int mx = i;
      for (int j = i - 1; j >= 0; --j)
        if (a[j] > a[mx]) mx = j;      
      if (mx < i) {
        if (mx > 0) {
          cout << d - mx << ' ';
          flip(a, mx);
        }
        cout << d - i << ' ';
        flip(a, i);
      }
    }
    cout << "0\n";
  }
}