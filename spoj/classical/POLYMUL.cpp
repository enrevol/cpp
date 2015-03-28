#include <algorithm>
#include <cassert>
#include <complex>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
 
const uint32_t N = 32768;
const long double PI = 3.14159265358979;

struct point {
    using T = long double;
    
    T real;
    T imag;
    
    point(T real = 0, T imag = 0) : real(real), imag(imag) { }
    
    friend
    point operator*(const point& lhs, const point& rhs) {
        return point(lhs.real * rhs.real - lhs.imag * rhs.imag, lhs.real * rhs.imag + lhs.imag * rhs.real);
    }
    
    friend
    point operator+(const point& lhs, const point& rhs) {
        return point(lhs.real + rhs.real, lhs.imag + rhs.imag);
    }
    
    friend
    point operator-(const point& lhs, const point& rhs) {
        return point(lhs.real - rhs.real, lhs.imag - rhs.imag);
    }
    
    void operator/=(int32_t n) {
        real /= n;
    }
};

uint32_t rev[N];
uint32_t a[N], b[N];
int64_t c[N];
point x[N];
point pa[N], pb[N], pc[N];

uint32_t next_power(uint32_t x) {
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    ++x;
    return x;
}

void fft(point* input, uint32_t n, bool invert) {
    uint32_t dig = std::__lg(n);
    for (uint32_t i = 1; i < n; ++i) {
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (dig - 1));
		if (rev[i] > i) {
			std::swap(input[i], input[rev[i]]);
		}
    }
    for (uint32_t L = 1; L <= dig; ++L) {
        uint32_t len = 1U << L;
        long double angle = 2 * PI / len;
        if (invert) {
            angle *= -1;
        }
        point w(cos(angle), sin(angle));
        x[0] = point(1);
        for (uint32_t i = 1; i < len / 2; ++i) {
            x[i] = x[i - 1] * w;
        }
        for (uint32_t i = 0; i < n; i += len) {
            for (uint32_t j = 0; j < len / 2; ++j) {
                point a = input[i + j];
                point b = x[j] * input[i + j + len / 2];
                input[i + j] = a + b;
                input[i + j + len / 2] = a - b;
            }
        }
    }
    if (invert) {
        for (uint32_t i = 0; i < n; ++i) {
            input[i] /= n;
        }
    }
}

void mul(uint32_t* a, uint32_t* b, int64_t *c, uint32_t n) {
    uint32_t size = n * 2;
    size = next_power(size);
    for (uint32_t i = 0; i < n; ++i) {
        pa[i] = point(a[i], 0);
        pb[i] = point(b[i], 0);
    }
    std::fill(pa + n, pa + size, point());
    std::fill(pb + n, pb + size, point());
    fft(pa, size, false);
    fft(pb, size, false);
    for (uint32_t i = 0; i < size; ++i) {
        pc[i] = pa[i] * pb[i];
    }
    fft(pc, size, true);
    for (uint32_t i = 0; i < size; ++i) {
        c[i] = pc[i].real + .8;
    }
}

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    uint32_t tt;
    std::cin >> tt;
    while (tt--) {
        uint32_t n;
        std::cin >> n;
        for (int32_t i = n; i >= 0; --i) {
            std::cin >> a[i];
        }
        for (int32_t i = n; i >= 0; --i) {
            std::cin >> b[i];
        }
        mul(a, b, c, n + 1);
        for (int32_t i = 2 * n; i >= 0; --i) {
            std::cout << c[i] << ' ';
        }
        std::cout << '\n';
    }
}