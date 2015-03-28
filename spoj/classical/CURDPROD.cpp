#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

constexpr int N = 10010;

int a[N];

int main() {
//    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        int n, t;
        cin >> n >> t;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        long long low = 1;
        long long high = 1LL << 60;
        long long answer = 0;
        while (low <= high) {
            long long mid = (low + high) / 2;
            long long sum = 0;
            for (int i = 1; i <= n; ++i) {
                sum += mid / a[i];
            }
            if (sum >= t) {
                answer = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        cout << answer << '\n';
    }
}