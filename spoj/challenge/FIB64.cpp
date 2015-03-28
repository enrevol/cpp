#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include <unistd.h>

const uint32_t INF_32 = 0x7FFFFFFF;
const uint64_t INF_64 = 0x7FFFFFFFFFFFFFFF;
const uint64_t MIN = 0x8000000000000000;

class FastInput {
    size_t m_dataOffset, m_dataSize;
    uint64_t m_v;
    uint8_t m_buffer[32768];
    uint64_t m_data[8192];
    
public:
    FastInput() {
        m_dataOffset = 0;
        m_dataSize = 0;
        m_v = MIN;
    }
    
    uint64_t ReadNext() {
        if (m_dataOffset == m_dataSize) {
            int r = read(0, m_buffer, sizeof(m_buffer));
            if (r <= 0) return m_v;
            m_dataOffset = 0;
            m_dataSize = 0;
            int i = 0;
            if (m_buffer[0] < '0') {
                if (m_v != MIN) {
                    m_data[m_dataSize++] = m_v;
                    m_v = MIN;
                }
                for (; (i < r) && (m_buffer[i] < '0'); ++i);
            }
            for (; i < r;) {
                if (m_buffer[i] >= '0') {
                    m_v = m_v * 10 + m_buffer[i] - 48;                    
                    ++i;
                } else {
                    m_data[m_dataSize++] = m_v;
                    m_v = MIN;
                    for (i = i + 1; (i < r) && (m_buffer[i] < '0'); ++i);
                }
            }
        }
        return m_data[m_dataOffset++];
    }
};

FastInput g_fi;

const uint32_t SZ = 5;

uint32_t aa[1 << SZ], bb[1 << SZ];

namespace high {

uint64_t solve(uint64_t n, int64_t m) {
    int32_t k = std::__lg(n) + 1;
    uint64_t a = aa[n >> (k - SZ)];
    uint64_t b = bb[n >> (k - SZ)];
    k = k - SZ;
    while (k--) {
        long double x = (long double)(int64_t(a));
        int64_t z = b + b - a;
        int64_t d = int64_t(a * z - int64_t(x * z / m) * m);
        while (d >= m) d = d - m;
        while (d < 0) d = d + m;
        long double y = (long double)(int64_t(b));
        int64_t e = int64_t(a * a - int64_t((x * a + y * b) / m) * m + b * b);
        while (e >= m) e = e - m;
        while (e < 0) e = e + m;
        a = d;
        b = e;
        if ((n >> k) & 1) {
            uint64_t c = a + b;
            a = b;
            b = c;
        }
    }
    return a;
}

}

namespace low {

inline
uint32_t add(uint32_t a, uint32_t b, uint32_t m) {
    return a + b < m ? a + b : a + b - m;
}

uint32_t mul(uint32_t a, uint32_t b, uint32_t m) {
    return 1ULL * a * b >= m ? 1ULL * a * b % m : a * b;
}

uint32_t solve(uint64_t n, uint32_t m) {
    int32_t k = std::__lg(n) + 1;
    uint32_t a = aa[n >> (k - SZ)];
    uint32_t b = bb[n >> (k - SZ)];
    k = k - SZ;
    while (k--) {
        uint32_t d = mul(a, b + b >= a ? b + b - a : b + b + m - a, m);
        uint32_t e = add(mul(a, a, m), mul(b, b, m), m);
        a = d;
        b = e;
        if ((n >> k) & 1) {
            uint32_t c = add(a, b, m);
            a = b;
            b = c;
        }
    }
    return a;
}

}

void init() {
    for (uint32_t n = 0; n < 1 << SZ; ++n) {
        int32_t k = std::__lg(n) + 1;
        uint32_t a = 0;
        uint32_t b = 1;
        while (k--) {
            uint32_t d = a * (b + b - a);
            uint32_t e = a * a + b * b;
            a = d;
            b = e;
            if ((n >> k) & 1) {
                uint32_t c = a + b;
                a = b;
                b = c;
            }
        }
        aa[n] = a;
        bb[n] = b;
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    init();
    for (int i = 1; i <= 330000; ++i) {
        uint64_t n = g_fi.ReadNext();
        uint64_t m = g_fi.ReadNext();
        if (m <= INF_32) {
            printf("%u\n", low::solve(n, m));
        } else {
            printf("%llu\n", high::solve(n, m));
        }
    }
}