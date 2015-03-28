#include <algorithm>
#include <iostream>
#include <forward_list>
#include <string>
#include <vector>

const int N_MAX = 10000;

std::forward_list<int> stack[N_MAX + 1];

int main() {
//    freopen("input.txt", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int tt;
    std::cin >> tt;
    for (int tn = 1; tn <= tt; ++tn) {
        std::cout << "Case " << tn << ":\n";
        int n, q;
        std::cin >> n >> q;
        for (int i = 1; i <= n; ++i) {
            stack[i].clear();
        }
        while (q--) {
            std::string type;
            int arg1, arg2;
            std::cin >> type >> arg1;
            if (type == "push") {
                std::cin >> arg2;
                stack[arg1].push_front(arg2);
            } else if (type == "pop") {
                if (!stack[arg1].empty())
                    stack[arg1].pop_front();
            } else if (type == "put") {
                std::cin >> arg2;
                stack[arg1].splice_after(stack[arg1].before_begin(), stack[arg2]);
            } else {
                if (!stack[arg1].empty()) {
                    std::cout << stack[arg1].front() << '\n';
                } else {
                    std::cout << "Empty!" << '\n';
                }
            }
        }
    }
}