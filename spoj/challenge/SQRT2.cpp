#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

constexpr uint32_t MOD = (1U << 22) * 112 + 1;

uint32_t rev[1 << 22];
uint32_t __root[2][1 << 22], __reci[2][1 << 22];
uint32_t *root[2][23], *reci[2][23];

uint32_t pow_mod(uint32_t a, uint32_t b) {
    uint32_t r = 1;
    while (b) {
        if (b & 1) r = uint64_t(r) * a % MOD;
        b >>= 1;
        a = uint64_t(a) * a % MOD;
    }
    return r;
}

void reduction(uint32_t& x) {
    x -= (~(int32_t(x - MOD) >> 31)) & MOD;
}

constexpr
uint32_t mul_mod(uint32_t a, uint32_t b, uint32_t r) {
    return uint64_t(b) * a - uint64_t((uint64_t(r) * a) >> 32) * MOD;
}

constexpr
uint32_t get_reci(uint32_t x) {
    return (uint64_t(x) << 32) / MOD;
}

void compress(vector<uint32_t>& x) {
    uint32_t carry = 0;
    for (uint32_t i = 0; i < x.size(); ++i) {
        carry += x[i];
        x[i] = carry % 10;
        carry /= 10;
    }
    while (carry > 0) {
        x.push_back(carry % 10);
        carry /= 10;
    }
    while (x.size() > 1 && x.back() == 0) {
        x.pop_back();
    }
}

vector<uint32_t> fft(const vector<uint32_t>& input, uint32_t n, bool invert) {
    vector<uint32_t> result(n);
    copy(input.begin(), input.end(), result.begin());
    uint32_t dig = 0;
    while ((1U << dig) < n) {
        ++dig;
    }
    for (uint32_t i = 1; i < n; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (dig - 1));
        if (rev[i] > i) {
            swap(result[i], result[rev[i]]);
        }
    }
    for (uint32_t L = 1; L <= dig; ++L) {
        uint32_t len = 1U << L;
        for (uint32_t i = 0; i < n; i += len) {
            for (uint32_t j = 0; j < len / 2; ++j) {
                uint32_t a = result[i + j];
                uint32_t b = mul_mod(result[i + j + len / 2], root[invert][L][j], reci[invert][L][j]);
                reduction(a);
                result[i + j] = a + b;
                result[i + j + len / 2] = a + MOD + MOD - b;
                reduction(result[i + j + len / 2]);
            }
        }
    }
    if (invert) {
        uint32_t x = pow_mod(n, MOD - 2);
        uint32_t r = get_reci(x);
        for (uint32_t i = 0; i < n; ++i) {
            result[i] = mul_mod(result[i], x, r);
            reduction(result[i]);
        }
    }
    return result;
}
    
vector<uint32_t> mul(const vector<uint32_t>& lhs, const vector<uint32_t>& rhs) {
    uint32_t size = lhs.size() + rhs.size() - 1;
    uint32_t temp = 1;
    while (temp < size) {
        temp <<= 1;
    }
    size = temp;
    vector<uint32_t> pa = fft(lhs, size, false);
    if (&rhs == &lhs) {
        for (uint32_t i = 0; i < size; ++i) {
            pa[i] = uint64_t(pa[i]) * pa[i] % MOD;
        }
    } else {
        vector<uint32_t> pb = fft(rhs, size, false);
        for (uint32_t i = 0; i < size; ++i) {
            pa[i] = uint64_t(pa[i]) * pb[i] % MOD;
        }
    }
    vector<uint32_t> result = fft(pa, size, true);
    compress(result);
    return result;
}
    
ostream& operator<<(ostream& os, const vector<uint32_t>& x) {
    for (int32_t i = x.size() - 1; i >= 0; --i) {
        os << x[i];
    }
    return os;
}

int main() {
//    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    uint32_t pos = 0;
    for (uint32_t L = 1; L <= 22; ++L) {
        uint32_t len = 1U << L;
        uint32_t u = pow_mod(3, (MOD - 1) / len);
        uint32_t v = pow_mod(u, MOD - 2);
        uint32_t ru = get_reci(u);
        uint32_t rv = get_reci(v);
        root[0][L] = &__root[0][pos];
        root[1][L] = &__root[1][pos];
        reci[0][L] = &__reci[0][pos];
        reci[1][L] = &__reci[1][pos];
        uint32_t x = 1, y = 1;
        for (uint32_t i = 0; i < len / 2; ++i) {
            root[0][L][i] = x;
            root[1][L][i] = y;
            reci[0][L][i] = get_reci(x);
            reci[1][L][i] = get_reci(y);
            x = mul_mod(x, u, ru);
            reduction(x);
            y = mul_mod(y, v, rv);
            reduction(y);
        }
        pos += len / 2;
    }
    vector<uint32_t> x;
    x.push_back(1);
    x.push_back(7);
    x.push_back(0);
    x.push_back(7);
    for (uint32_t i = 3; i <= 21; ++i) {
        uint32_t k = 1U << i;
        vector<uint32_t> s = mul(x, x);
        s.front() = 10 - s.front();
        for (uint32_t i = 1; i < s.size() - 1; ++i) {
            s[i] = 9 - s[i];
        }
        s.back() = 4 - s.back();
        s.push_back(1);
        x = mul(x, s);
        copy(x.end() - k, x.end(), x.begin());
        x.resize(k);
    }
    for (uint32_t i = 0, carry = 0; i < x.size(); ++i) {
        carry = (x[i] << 1) + carry;
        x[i] = carry % 10;
        carry /= 10;
    }
    cout << "1.";
    cout << x << '\n';
}