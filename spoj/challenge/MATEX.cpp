#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>

#include <unistd.h>

class FastInput {
    size_t m_dataSize;
    size_t m_dataOffset;
    uint64_t m_v;
    uint8_t m_buffer[32768];
    uint64_t m_data[8192];
    
public:
    FastInput() {
        m_dataSize = 0;
        m_dataOffset = 0;
        m_v = 0x8000000000000000;
    }
    
    uint64_t ReadNext() {
        if (m_dataOffset == m_dataSize) {
            int r = read(0, m_buffer, sizeof(m_buffer));
            if (r <= 0) return m_v;
            m_dataOffset = 0;
            m_dataSize = 0;
            int i = 0;
            if (m_buffer[0] < '0') {
                if (m_v != 0x8000000000000000) {
                    m_data[m_dataSize++] = m_v;
                    m_v = 0x8000000000000000;
                }
                for (; (i < r) && (m_buffer[i] < '0'); ++i);
            }
            for (; i < r;) {
                if (m_buffer[i] >= '0') {
                    m_v = m_v * 10 + m_buffer[i] - 48;
                    ++i;
                } else {
                    m_data[m_dataSize++] = m_v;
                    m_v = 0x8000000000000000;
                    for (i = i + 1; (i < r) && (m_buffer[i] < '0'); ++i);
                }
            }
        }
        return m_data[m_dataOffset++];
    }
} g_fi;

class FastOutput {
    size_t m_dataOffset;
    uint8_t m_data[32768];
    
public:
    FastOutput() {
        m_dataOffset = 0;
    }
    
    ~FastOutput() {
    }

    void Flush() {
        if (m_dataOffset) {
            if (write(1, m_data, m_dataOffset)) {
                m_dataOffset = 0;
            }
        }
    }

    void PrintUint(uint32_t v, char d) {
        if (m_dataOffset + 11 > sizeof(m_data)) Flush();
        if (v < 100000) {
            if (v < 1000) {
                if (v < 10) {
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 1;
                } else if (v < 100) {
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 2;
                } else {
                    m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 3;
                }
            } else {
                if (v < 10000) {
                    m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 4;
                } else {
                    m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 5;
                }
            }
        } else {
            if (v < 100000000) {
                if (v < 1000000) {
                    m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 6;
                } else if (v < 10000000) {
                    m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 7;
                } else {
                    m_data[m_dataOffset + 7] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 8;
                }
            } else {
                if (v < 1000000000) {
                    m_data[m_dataOffset + 8] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 7] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 9;
                } else {
                    m_data[m_dataOffset + 9] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 8] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 7] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 10;
                }
            }
        }
        m_data[m_dataOffset++] = d;
    }

    void PrintChar(char d) {
        if (m_dataOffset + 1 > sizeof(m_data)) Flush();
        m_data[m_dataOffset++] = d;
    }

    void ReplaceChar(int offset, char d) {
        m_data[m_dataOffset + offset] = d;
    }    
} g_fo;

constexpr uint32_t W = 18;
constexpr uint32_t MOD = 1000000007;

struct matrix {
    uint32_t a[W][W];
} t[60], id, dp[6][1024];

constexpr uint32_t fast_mod(uint64_t x) {
    return ((x & 0xFFFFFFFF) + ((x >> 32) * (0x100000000 % MOD))) % MOD;
}

void mul(matrix& r, const matrix& x, const matrix& y) {
    for (uint32_t i = 0; i < W; ++i)
        for (uint32_t j = 0; j < W; ++j) {
            uint64_t v = 0;
            for (uint32_t k = 0; k < W; ++k) {
                v += uint64_t(x.a[i][k]) * y.a[k][j];
            }
            r.a[i][j] = fast_mod(v);
        }
}

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
//    std::cin.tie(nullptr);
//    std::ios::sync_with_stdio(false);
    uint32_t zzz = g_fi.ReadNext();
    for (uint32_t i = 0; i < W; ++i) {
        id.a[i][i] = 1;
    }
    for (uint32_t i = 0; i < W; ++i)
        for (uint32_t j = 0; j < W; ++j) {
            t[0].a[i][j] = g_fi.ReadNext();
        }
    for (uint32_t i = 1; i < 60; ++i) {
        mul(t[i], t[i - 1], t[i - 1]);
    }
    for (uint32_t i = 0; i < 6; ++i) {
        dp[i][0] = id;
        for (uint32_t mask = 1; mask < 1024; ++mask) {
            uint32_t v = mask & -mask;
            mul(dp[i][mask], dp[i][mask - v], t[i * 10 + __builtin_ctz(v)]);
        }
    }
    for (uint32_t i = 0; i < 280000; ++i) {
        uint32_t x = g_fi.ReadNext();
        uint32_t y = g_fi.ReadNext();
        uint64_t k = g_fi.ReadNext();
        --x, --y;
        matrix* list[6];
        uint32_t cnt = 0;
        for (uint32_t i = 0; k; k >>= 10, ++i)
            if (k & 1023) {
                list[cnt++] = &dp[i][k & 1023];
            }
        uint32_t arr[2][W];
        for (uint32_t i = 0; i < W; ++i) {
            arr[0][i] = list[cnt - 1]->a[i][y];
        }
        uint32_t f = 0;
        for (uint32_t i = cnt - 2; i > 0; --i) {
            for (uint32_t j = 0; j < W; ++j) {
                uint64_t v = 0;
                for (uint32_t p = 0; p < W; ++p) {
                    v += uint64_t(list[i]->a[j][p]) * arr[f][p];
                }
                arr[f ^ 1][j] = fast_mod(v);
            }
            f ^= 1;
        }
        uint64_t v = 0;
        for (uint32_t i = 0; i < W; ++i) {
            v += uint64_t(list[0]->a[x][i]) * arr[f][i];
        }
        g_fo.PrintUint(fast_mod(v), '\n');
    }
    g_fo.Flush();
}