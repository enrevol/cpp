#include <algorithm>
#include <iostream>
#include <functional>
#include <set>
#include <string>
#include <vector>

int main() {
//    freopen("input.txt", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    while (std::cin >> s) {
        for (int len = 1; len <= 3; ++len) {
            std::set<std::string> st;
            for (int i = 0; i + len - 1 < int(s.size()); ++i) {
                st.insert(s.substr(i, len));
            }
            std::string ans;
            while (int(ans.size()) < len) ans = ans + '0';
            std::function<bool(int)> dfs = [len, &st, &ans, &dfs] (int cur) {
                if (cur >= len) return !st.count(ans);
                for (ans[cur] = 'A'; ans[cur] <= 'Z'; ++ans[cur])
                    if (dfs(cur + 1))
                        return true;
                return false;
            };
            if (dfs(0)) {
                std::cout << ans << '\n';
                break;
            }
        }
    }
}