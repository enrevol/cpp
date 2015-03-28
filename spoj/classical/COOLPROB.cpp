#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <functional>
#include <set>
#include <string>
#include <vector>

const int N = 1234;

int a[N];
double c[N], s[N];

int main() {
//    freopen("input.txt", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    c[1] = 1;
    for (int i = 2; i < N; ++i) {
        c[i] = c[i - 1] * .99;
        s[i] = c[i] + s[i - 1];
    }
    int tt;
    std::cin >> tt;
    while (tt--) {
        int n, x;
        std::cin >> n >> x;
        double ans = 0;
        for (int i = 3; i <= n; ++i) {
            ans += s[n - 1] * (i - 1) * (i - 2) / (n * (n - 1) * (n - 2));
        }
        std::cout << std::fixed << std::setprecision(6) << ans << '\n';
    }
}