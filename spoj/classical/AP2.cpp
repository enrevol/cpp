#include <iostream>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        long long a, b, s;
        std::cin >> a >> b >> s;
        int c = 2 * s / (a + b);
        std::cout << c << '\n';
        for (int i = -2; i <= c - 3; ++i) {
            std::cout << a + i * (b - a) / (c - 5) << ' ';
        }
    }
}