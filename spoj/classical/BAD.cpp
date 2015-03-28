#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>

const int N = 255;

struct player {
    int mask[8];
    
    inline
    void set(int p) {
        mask[p >> 5] |= 1 << (p & 31);
    }
} p[N];

int main() {
//    freopen("input.txt", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int tt;
    std::cin >> tt;
    while (tt--) {
        int n;
        std::cin >> n;
        std::for_each(std::begin(p), std::end(p), [] (player& p) {
            std::fill(std::begin(p.mask), std::end(p.mask), 0);
        } );
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < i; ++j) {
                int a, b;
                std::cin >> a >> b;
                --a, --b;
                p[a].set(b);
            }
        int index = -1, best = 0;
        for (int i = n - 1; i >= 0; --i) {
//            std::cerr << "i = " << i << '\n';
            player r;
            std::copy(std::begin(p[i].mask), std::end(p[i].mask), std::begin(r.mask));
            for (int j = 0; j < n; ++j)
                if ((p[i].mask[j >> 5] >> (j & 31)) & 1) {
//                    std::cerr << "  j = " << j << '\n';
                    for (int k = 0; k < 8; ++k) {
                        r.mask[k] |= p[j].mask[k];
                    }
                }
            int val = 0;
            for (int j = 0; j < 8; ++j) {
                val += __builtin_popcount(r.mask[j]);
            }
//            std::cerr << "  val = " << val << '\n';
            if (val > best) {
                best = val;
                index = i;
            } else if (val == best) {
                index = i;
            }
        }
        std::cout << index + 1 << ' ' << best << '\n';
    }
}