#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
int main() {
  //freopen("input.txt", "r", stdin);
    int T;
    cin >> T;
    getchar();
    while (T--) {
        string s;
        getline(std::cin, s, '\n');
        int cnt[26];
        fill(cnt, cnt + 26, 0);
        for (int i = 0; i < s.length(); ++i)
      if (s[i] != ' ') cnt[s[i] - 'A']++;
        int m = 0, mcnt = 0;
        for (int i = 0; i < 26; ++i)
            if (cnt[i] > cnt[m]) m = i;
        for (int i = 0; i < 26; ++i)
            if (cnt[i] == cnt[m]) mcnt++;
        if (mcnt == 1) {
            int k = m - ('E' - 'A');
            if (k < 0) k += 26;
            cout << k << ' ';
            char c;
            for (int i = 0; i < s.size(); ++i) {
              c = s[i];
        if (c != ' ') {
          c -= k;
          while (c < 'A') c += 26;
          while (c > 'Z') c -= 26;              
        }
        cout << c;
            }
            cout << '\n';
        } else {
            cout << "NOT POSSIBLE\n";
        }           
    }
}