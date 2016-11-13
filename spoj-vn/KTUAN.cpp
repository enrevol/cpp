#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cinttypes>
#include <vector>

using namespace std;

constexpr uint32_t MOD = 1000000000;
constexpr uint32_t N = 100000;
constexpr uint32_t P = 260;

int32_t p[2 * (P + 1)]; // A001318
int32_t _a[N + N];      // A000041
int32_t* a = _a + N;

int32_t solve(int32_t n) {
    int32_t& ret = a[n];
    if (ret == -1) {
        int64_t sum = 0;
        for (int32_t i = 1; p[i] <= n; i += 4) {
            sum += solve(n - p[i]) + solve(n - p[i + 1]);
            sum -= solve(n - p[i + 2]) + solve(n - p[i + 3]);
        }
        ret = sum % MOD;
    }
    return ret;
}

int main() {
    //    freopen("in", "r", stdin);
    uint32_t n;
    scanf("%" SCNu32, &n);
    uint32_t answer = 0;
    if (n > 0) {
        std::memset(a, -1, (N + 1) * 4);
        a[0] = a[1] = 1;
        for (uint32_t i = 1, j = 1; i <= P; ++i, j += 2) {
            p[j] = i * (3 * i - 1) / 2;
            p[j + 1] = p[j] + i;
        }
        int32_t val = solve(n);
        answer = val < 0 ? val + MOD : val;
    }
    printf("%" PRIu32, answer);
}
