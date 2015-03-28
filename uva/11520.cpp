#include <iostream>
#include <string>
using namespace std;
int main() {
  ios::sync_with_stdio(0);
  int tt, nCase = 0;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    string s[15];
    for (int i = 0; i < n; ++i)
      cin >> s[i];
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (s[i][j] == '.')
          for (int k = 'A'; ; ++k) {
            if (i > 0 && s[i - 1][j] == k) continue;
            if (j > 0 && s[i][j - 1] == k) continue;
            if (i < n - 1 && s[i + 1][j] == k) continue;
            if (j < n - 1 && s[i][j + 1] == k) continue;
            s[i][j] = k;
            break;
          }      
    cout << "Case " << ++nCase << ":\n";
    for (int i = 0; i < n; ++i)
      cout << s[i] << '\n';
  }
}