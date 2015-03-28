#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

const int K = 8;
const int N = 25000 / K;
const int BASE = 100000000;

int a[N], b[N], c[N];

void convert(const std::string& s, int x[], int& n) {
    n = 0;
    int sz = s.size();
    for (int i = sz - 1; i >= 0; i -= K) {
        int v = 0;
        for (int j = std::max(i - K + 1, 0); j <= i; ++j) {
            v = v * 10 + s[j] - 48;
        }
        x[++n] = v;
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w",stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int tt;
    std::cin >> tt;
    while (tt--) {
        std::string sa, sb;
        std::cin >> sa >> sb;
        int na, nb;
        convert(sa, a, na);
        convert(sb, b, nb);
        long long v = 0;
        for (int i = 1; i <= na + nb - 1; ++i) {
            for (int j = std::max(1, i - nb + 1); j <= na && j <= i; ++j) {
                v += 1LL * a[j] * b[i - j + 1];
            }
            c[i] = v % BASE;
            v = v / BASE;
        }
        int nc = na + nb - 1;
        if (v > 0) c[++nc] = v;
        std::cout << c[nc];
        for (int i = nc - 1; i >= 1; --i) {
            int d = 1;
            for (int t = c[i] / 10; t; t /= 10) ++d;
            while (d++ < K) std::cout << '0';
            std::cout << c[i];
        }
        std::cout << '\n';
    }
}