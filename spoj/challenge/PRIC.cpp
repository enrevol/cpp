#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#define fast_mod(x, y) ((x) - (x) / (y) * (y))
#define get(n) ((sieve[(n) >> 6U] >> (n >> 1U)) & 1U)
#define set(n) sieve[(n) >> 6U] |= 1U << ((n) >> 1U)

#define get_t1(n) ((table1[(n) >> 5U] >> (n)) & 1U)
#define get_t2(n) ((table2[(n) >> 5U] >> (n)) & 1U)
#define set_t1(n) table1[(n) >> 5U] |= 1U << (n)
#define set_t2(n) table2[(n) >> 5U] |= 1U << (n)

#define div_37(n) (n * 2437684141U <= 116080197U)
#define div_41(n) (n * 3247414297U <= 104755299U)
#define div_43(n) (n * 799063683U <= 99882960U)
#define div_47(n) (n * 1736263375U <= 91382282U)

#define check(n) (!get_t1(fast_mod((n), T_SIZE1)) && \
                  !get_t2(fast_mod((n), T_SIZE2)) && \
                  !div_37(n) && \
                  !div_41(n) && \
                  !div_43(n) && \
                  !div_47(n) && \
                  !get(n))

const uint32_t N = 0x7FFFFFFF;
const uint32_t SQRT = 46330;
const uint32_t MAX = 33333333;
const uint32_t BUCKET_SIZE = 1 << 20;
const uint32_t BUCKET = (N - 1) / BUCKET_SIZE + 1;

uint32_t sieve[(N >> 6) + 30000];
uint32_t p[SQRT], pos1[SQRT], pos2[SQRT];
uint8_t mark[(SQRT >> 1) + 1];

const uint32_t T_SIZE1 = 3 * 5 * 7 * 11 * 13 * 17; // 255255
const uint32_t T_SIZE2 = 19 * 23 * 29 * 31; // 392863

uint32_t table1[(T_SIZE1 >> 5) + 1];
uint32_t table2[(T_SIZE2 >> 5) + 1];

char s[1010101];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    for (uint32_t i = 0; i < T_SIZE1; i +=  3) set_t1(i);
    for (uint32_t i = 0; i < T_SIZE1; i +=  5) set_t1(i);
    for (uint32_t i = 0; i < T_SIZE1; i +=  7) set_t1(i);
    for (uint32_t i = 0; i < T_SIZE1; i += 11) set_t1(i);
    for (uint32_t i = 0; i < T_SIZE1; i += 13) set_t1(i);
    for (uint32_t i = 0; i < T_SIZE1; i += 17) set_t1(i);
    for (uint32_t i = 0; i < T_SIZE2; i += 19) set_t2(i);
    for (uint32_t i = 0; i < T_SIZE2; i += 23) set_t2(i);
    for (uint32_t i = 0; i < T_SIZE2; i += 29) set_t2(i);
    for (uint32_t i = 0; i < T_SIZE2; i += 31) set_t2(i);
    uint32_t pn = 0;
    for (uint32_t i = 3U; i <= SQRT; i += 2U)
        if (!mark[i >> 1U]) {
            if (i > 47) {
                p[pn] = i << 1U;
                pos1[pn] = i * i;
                switch (i % 30U) {
                case  7: set(pos1[pn]), pos1[pn] += p[pn] * 2U;
                case 11: set(pos1[pn]), pos1[pn] += p[pn];
                case 13: set(pos1[pn]), pos1[pn] += p[pn] * 2U;
                case 17: set(pos1[pn]), pos1[pn] += p[pn];
                case 19: set(pos1[pn]), pos1[pn] += p[pn] * 2U;
                case 23: set(pos1[pn]), pos1[pn] += p[pn] * 3U;
                case 29: set(pos1[pn]), pos1[pn] += p[pn];
                }
                pos2[pn] = pos1[pn] + p[pn] * 6U;
                ++pn;
            }
            for (uint32_t j = i * i; j <= SQRT; j += i << 1U) {
                mark[j >> 1U] = 1U;
            }
        }
    uint32_t loop = 0;
    sieve[0] = 1U;
    for (uint32_t l = 0, r = BUCKET_SIZE - 1; loop < BUCKET; l += BUCKET_SIZE, r += BUCKET_SIZE) {
        for (uint32_t i = 0; i < pn; ++i) {
            while (pos1[i] <= r) {
                set(pos1[i]);
                set(pos1[i] + p[i] * 3U);
                set(pos1[i] + p[i] * 5U);
                set(pos1[i] + p[i] * 8U);
                pos1[i] += p[i] * 15U;
                set(pos2[i]);
                set(pos2[i] + p[i] * 3U);
                set(pos2[i] + p[i] * 5U);
                set(pos2[i] + p[i] * 8U);
                pos2[i] += p[i] * 15U;
            }
        }
        ++loop;
    }
    uint32_t a = 1;
    for (uint32_t i = 0; i < 33U; ++i) {
        uint32_t size = 0;
        for (uint32_t j = 0; j < 1010101U; ++j) {
            s[size++] = '0' + check(a);
            a = (a + 1234567890) & 0x7FFFFFFF;
        }
        fwrite(s, 1, size, stdout);
    }
}