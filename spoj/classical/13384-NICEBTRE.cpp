#include <iostream>
#include <string>
using namespace std;
int main() {
  int T;
  cin >> T;
  string s;
  while (T--) {
    cin >> s;
    int pos[10005];
    fill(pos, pos + 20, 0);
    int depth = 0, ans = 0;
    pos[0] = 0;
    for (int i = 0; i < s.size(); ++i) {
      pos[depth]++;
      if (s[i] == 'n') {        
        depth++;
        ans = max(ans, depth);
        pos[depth] = 0;
      } else {        
        while (pos[depth] == 2) depth--;
      }
    }
    cout << ans << '\n';
  }  
} 