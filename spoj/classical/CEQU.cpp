#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
//    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int tt;
    cin >> tt;
    for (int tn = 1; tn <= tt; ++tn) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << "Case " << tn << ": " << (c % __gcd(a, b) == 0 ? "Yes" : "No") << '\n';
    }
}