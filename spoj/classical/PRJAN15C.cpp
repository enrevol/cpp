#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

const int N = 1234567;

std::string s;
int cnt[26];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    while (std::cin >> s) {
        std::fill(std::begin(cnt), std::end(cnt), 0);
        for (char c : s) {
            cnt[c - 'a']++;
        }
        int n = s.size();
        long long ans = 1LL * n * n;
        for (int i = 0; i < 26; ++i) {
            int a = cnt[i] - (s[0] == ('a' + i));
            int b = cnt[i] - (s[n - 1] == ('a' + i));
            ans = ans - 1LL * a * b;
        }
        std::cout << ans << '\n';
    }
}