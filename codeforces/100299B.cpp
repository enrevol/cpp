#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
stringstream ss;
set<string> st;
vector<string> ans;
int main() {
  //freopen("input.txt", "r", stdin);
  int T;
  cin >> T;
  string str, s1, s2, s3, sounds;
  while (getline(cin, str, '\n')) {
    if (str == "what does the fox say?") {
      ss.clear();
      ss.str(sounds);
      ans.clear();
      while (ss >> s1) {
        if (!st.count(s1)) {
          ans.push_back(s1);
        }
      }
      for (int i = 0; i < ans.size() - 1; ++i) {
        cout << ans[i] << ' ';
      }
      cout << ans[ans.size() - 1] << '\n';
      st.clear();
    } else {
      ss.clear();
      ss.str(str);
      s1 = s2 = s3 = "";
      ss >> s1 >> s2 >> s3;
      if (s2 != "goes") {
        sounds = str;
      } else {
        st.insert(s3);
      }
    }
  }
}