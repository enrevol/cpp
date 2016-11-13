//
//  meo-fft.cpp
//  mepcpp
//
//  Created by enrevol on 3/26/16.
//  Copyright © 2016 MEP. All rights reserved.
//

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>
#include <set>
#include <vector>

using SizeType = std::uint32_t;

class FftSolver {
public:
    using ElementType = std::uint32_t;

    static constexpr SizeType N = 17;
    static constexpr ElementType Mod = (1 << 18) * 22 + 1;
    static constexpr ElementType PrimitiveRoot = 4331862;

    void initialize(SizeType size) {
        assert((size & (size - 1)) == 0);

        size_ = size;
        log_ = 1;
        while ((1 << log_) < size_) {
            ++log_;
        }

        SizeType index = 0;
        for (SizeType l = 0; l < log_; ++l) {
            auto k = 1 << l;
            Modular u;
            Modular v;
            ElementType w = pow(PrimitiveRoot, (Mod - 1) / (k << 1));
            assert(pow(w, k << 1) == 1);
            u.init(w);
            v.init(pow(w, Mod - 2));
            roots_[0][l] = &cached_[0][index];
            roots_[1][l] = &cached_[1][index];
            ElementType x = 1;
            ElementType y = 1;
            for (SizeType i = 0; i < k; ++i) {
                roots_[0][l][i].init(x);
                roots_[1][l][i].init(y);
                x = reduction(u.multiply(x));
                y = reduction(v.multiply(y));
            }
            index += k;
        }
    }

    constexpr ElementType multiply(ElementType x, ElementType y) const {
        return (ElementType)(((std::uint64_t)x) * y % Mod);
    }

    std::vector<ElementType>
    multiply(const std::vector<ElementType>& lhs,
             const std::vector<ElementType>& rhs) const {
        auto totalSize = lhs.size() + rhs.size();
        SizeType size = 1;
        while (size < totalSize) {
            size <<= 1;
        }
        std::vector<ElementType> lhsPoints(size);
        for (SizeType i = 0; i < lhs.size(); ++i) {
            lhsPoints[i] = lhs[i];
        }
        dft(lhsPoints);
        if (&lhs == &rhs) {
            for (SizeType i = 0; i < size; ++i) {
                lhsPoints[i] = multiply(lhsPoints[i], lhsPoints[i]);
            }
            idft(lhsPoints);
        } else {
            std::vector<ElementType> rhsPoints(size);
            for (SizeType i = 0; i < rhs.size(); ++i) {
                rhsPoints[i] = rhs[i];
            }
            dft(rhsPoints);
            for (SizeType i = 0; i < size; ++i) {
                lhsPoints[i] = multiply(lhsPoints[i], rhsPoints[i]);
            }
            idft(lhsPoints);
        }
        return lhsPoints;
    }

    void dft(std::vector<ElementType>& input) const {
        // assert(input.size() == size_);
        // DIF.
        for (SizeType l = 0; l < log_; ++l) {
            SizeType k = 1 << (log_ - l - 1);
            for (SizeType i = 0; i < size_; i += k << 1) {
                for (SizeType j = 0; j < k; ++j) {
                    auto a = reduction(input[i + j]);
                    auto b = reduction(input[i + j + k]);
                    input[i + j] = a + b;
                    input[i + j + k] =
                        roots_[0][log_ - l - 1][j].multiply(a + Mod - b);
                }
            }
        }
    }

    void idft(std::vector<ElementType>& input) const {
        // assert(input.size() == size_);
        // DIT.
        for (SizeType l = 0; l < log_; ++l) {
            SizeType k = 1 << l;
            for (SizeType i = 0; i < size_; i += k << 1) {
                for (SizeType j = 0; j < k; ++j) {
                    auto a = input[i + j];
                    auto b =
                        reduction(roots_[1][l][j].multiply(input[i + j + k]));
                    input[i + j] = reduction(a + b);
                    input[i + j + k] = a + Mod - b;
                }
            }
        }
        Modular x;
        x.init(pow(size_, Mod - 2));
        for (SizeType i = 0; i < size_; ++i) {
            input[i] = reduction(x.multiply(input[i]));
        }
    }

private:
    SizeType size_;
    SizeType log_;

    struct Modular {
        ElementType val;
        ElementType rec;

        void init(ElementType val_) {
            val = val_;
            rec = (ElementType)(((std::uint64_t)(val) << 32) / Mod);
        }

        constexpr ElementType multiply(ElementType a) const {
            // return FftSolver().multiply(val, a);
            return (std::uint32_t)((std::uint64_t)val * a -
                                   (((std::uint64_t)rec * a) >> 32) * Mod);
        }
    };

    Modular cached_[2][1 << N];
    Modular* roots_[2][N];

    constexpr ElementType reduction(ElementType x) const {
        // return x % Mod;
        return x - ((~(((std::int32_t)(x - Mod)) >> 31)) & Mod);
    }

    constexpr ElementType pow(ElementType a, ElementType b) const {
        ElementType result = 1;
        while (b) {
            if (b & 1) {
                result = multiply(result, a);
            }
            b >>= 1;
            a = multiply(a, a);
        }
        return result;
    }
};

FftSolver solver;

using ResultMatrix = std::vector<std::uint32_t>;

class BaseMatrix {
public:
    using ElementType = std::uint32_t;
    using LineType = std::vector<ElementType>;

    static BaseMatrix getIdentityMatrix(SizeType size);

    BaseMatrix() = default;

    explicit BaseMatrix(const ResultMatrix& mat) {
        r[0].assign(mat.cbegin(), mat.cend());
        r[1].resize(mat.size());
        c[0].resize(mat.size());
        c[1].resize(mat.size());
    }

    LineType r[2]; ///< First two rows.
    LineType c[2]; ///< First two columns.

    void fill(SizeType n) {
        fillRows(n);
        fillColumns(n);
    }

    void resize(SizeType n, ElementType val = 0) {
        r[0].resize(n, val);
        r[1].resize(n, val);
        c[0].resize(n, val);
        c[1].resize(n, val);
    }

    SizeType getSize() const { return static_cast<SizeType>(r[0].size()); }

    ElementType get(SizeType row, SizeType col) const {
        if (row < 2) {
            return r[row][col];
        }
        if (col < 2) {
            return c[col][row];
        }
        auto delta = std::min(row - 1, col - 1);
        return get(row - delta, col - delta);
    }

    void set(SizeType row, SizeType col, ElementType val) {
        if (col < 2) {
            c[col][row] = val;
        }
        if (row < 2) {
            r[row][col] = val;
        }
    }

private:
    void fillRows(SizeType n) {
        r[0].reserve(n);
        r[1].reserve(n);
        // First column.
        if (n & 1) { // Odd.
            r[0].push_back(0);
            r[1].push_back(0);
        } else {
            r[0].push_back(2);
            r[1].push_back(2);
        }
        // 2nd column to (n-1)th column.
        for (SizeType i = 1; i + 1 < n; ++i) {
            if (i & 1) {
                r[0].push_back(1);
                r[1].push_back(1);
            } else {
                r[0].push_back(2);
                r[1].push_back(2);
            }
        }
        // Last column.
        if (n & 1) { // Odd.
            r[0].push_back(0);
            r[1].push_back(0);
        } else {
            r[0].push_back(2);
            r[1].push_back(2);
        }
    }

    void fillColumns(SizeType n) {
        c[0].reserve(n);
        c[1].reserve(n);
        if (n & 1) { // Odd.
            c[0].push_back(0);
            c[0].push_back(0);
        } else {
            c[0].push_back(2);
            c[0].push_back(2);
        }
        for (SizeType i = 2; i < n; ++i) {
            if ((n + i) & 1) {
                c[0].push_back(1);
            } else {
                c[0].push_back(2);
            }
        }
        c[1].push_back(1);
        c[1].push_back(1);
        c[1].push_back(2);
        for (SizeType i = 3; i < n; ++i) {
            c[1].push_back(0);
        }
    }
};

BaseMatrix BaseMatrix::getIdentityMatrix(SizeType size) {
    static BaseMatrix mat;
    mat.resize(size);
    mat.set(0, 0, 1);
    mat.set(1, 1, 1);
    return mat;
}

std::ostream& operator<<(std::ostream& os, const BaseMatrix& mat) {
    os << "---------------------------------" << std::endl;
    auto size = mat.getSize();
    for (SizeType i = 0; i < size; ++i) {
        for (SizeType j = 0; j < size; ++j) {
            auto v = mat.get(i, j);
            //            if (v == 2) v = -1;
            //            if (v == -2) v = 1;
            os << std::setw(3) << v;
        }
        os << std::endl;
    }
    os << "---------------------------------" << std::endl;
    return os;
}

BaseMatrix operator*(const BaseMatrix& lhs, const BaseMatrix& rhs) {
    BaseMatrix::LineType reversedC0(rhs.c[0].crbegin(), rhs.c[0].crend());
    BaseMatrix::LineType reversedC1(rhs.c[1].crbegin(), rhs.c[1].crend());

    // Unroll multiplication.
    auto totalSize = lhs.getSize() + rhs.getSize();
    SizeType alignedSize = 1;
    while (alignedSize < totalSize) {
        alignedSize <<= 1;
    }
    std::vector<FftSolver::ElementType> lhsR0(alignedSize);
    std::vector<FftSolver::ElementType> lhsR1(alignedSize);
    std::vector<FftSolver::ElementType> lhsC1(alignedSize);

    std::vector<FftSolver::ElementType> rhsR1(alignedSize);
    std::vector<FftSolver::ElementType> rhsC0(alignedSize);
    std::vector<FftSolver::ElementType> rhsC1(alignedSize);

    std::vector<FftSolver::ElementType> rhsC0Rev(alignedSize);
    std::vector<FftSolver::ElementType> rhsC1Rev(alignedSize);

    for (SizeType i = 0; i < lhs.getSize(); ++i) {
        lhsR0[i] = lhs.r[0][i];
        lhsR1[i] = lhs.r[1][i];
        lhsC1[i] = lhs.c[1][i];

        rhsR1[i] = rhs.r[1][i];
        rhsC0[i] = rhs.c[0][i];
        rhsC1[i] = rhs.c[1][i];

        rhsC0Rev[i] = reversedC0[i];
        rhsC1Rev[i] = reversedC1[i];
    }

    solver.dft(lhsR0);
    solver.dft(lhsR1);
    solver.dft(lhsC1);

    solver.dft(rhsR1);
    solver.dft(rhsC0);
    solver.dft(rhsC1);

    solver.dft(rhsC0Rev);
    solver.dft(rhsC1Rev);

    auto r0c1 = lhsR0;
    for (SizeType i = 0; i < alignedSize; ++i) {
        r0c1[i] = solver.multiply(r0c1[i], rhsC1Rev[i]);

        rhsC0Rev[i] = solver.multiply(rhsC0Rev[i], lhsR1[i]);
        rhsC1Rev[i] = solver.multiply(rhsC1Rev[i], lhsR1[i]);

        lhsR0[i] = solver.multiply(lhsR0[i], rhsR1[i]);
        lhsR1[i] = solver.multiply(lhsR1[i], rhsR1[i]);

        rhsC0[i] = solver.multiply(rhsC0[i], lhsC1[i]);
        rhsC1[i] = solver.multiply(rhsC1[i], lhsC1[i]);
    }

    solver.idft(r0c1);

    solver.idft(rhsC0Rev);
    solver.idft(rhsC1Rev);

    solver.idft(lhsR0);
    solver.idft(lhsR1);

    solver.idft(rhsC0);
    solver.idft(rhsC1);

    const auto& r1c0 = rhsC0Rev;
    const auto& r1c1 = rhsC1Rev;

    const auto& r0r1 = lhsR0;
    const auto& r1r1 = lhsR1;

    const auto& c1c0 = rhsC0;
    const auto& c1c1 = rhsC1;

    auto size = lhs.getSize();
    BaseMatrix result;
    result.resize(size);

    std::uint64_t c00 = 0;
    for (SizeType i = 0; i < size; ++i) {
        c00 += solver.multiply(lhs.get(0, i), rhs.get(i, 0));
    }
    result.set(0, 0, c00 % 3);

    result.set(0, 1, static_cast<BaseMatrix::ElementType>(r0c1[size - 1]) % 3);
    result.set(1, 0, static_cast<BaseMatrix::ElementType>(r1c0[size - 1]) % 3);
    result.set(1, 1, static_cast<BaseMatrix::ElementType>(r1c1[size - 1]) % 3);

    constexpr BaseMatrix::ElementType Adder = 600'000'000;

    // First two rows.
    for (SizeType r = 0; r < 2; ++r) {
        const auto& polyR = (r == 0 ? r0r1 : r1r1);
        const auto& polyC = (r == 0 ? r0c1 : r1c1);
        for (SizeType c = 2; c < size; ++c) {
            std::uint64_t v = Adder;
            v += (std::uint64_t)lhs.get(r, 0) * rhs.get(0, c);
            v += polyR[c + 1];
            if (c + 1 < size) {
                v -= (std::uint64_t)lhs.get(r, 0) * rhs.get(1, c + 1);
                v -= (std::uint64_t)lhs.get(r, c + 1) * rhs.get(1, 0);
                v += polyC[c + 1 + size - 3];
                v -= (std::uint64_t)lhs.get(r, c) * rhs.get(1, 1);
                v -= (std::uint64_t)lhs.get(r, c - 1) * rhs.get(0, 1);
            }
            result.set(r, c, v % 3);
        }
    }

    // First two columns.
    for (SizeType c = 0; c < 2; ++c) {
        const auto& polyC = (c == 0 ? c1c0 : c1c1);
        const auto& polyR = (c == 0 ? r1c0 : r1c1);
        for (SizeType r = 2; r < size; ++r) {
            std::uint64_t v = Adder;
            v += (std::uint64_t)lhs.get(r, 0) * rhs.get(0, c);
            v += polyC[r + 1];
            if (r + 1 < size) {
                v -= (std::uint64_t)lhs.get(0, 1) * rhs.get(r + 1, c);
                v -= (std::uint64_t)lhs.get(r + 1, 1) * rhs.get(0, c);
                v += polyR[2 + size - 2 - r];
                v -= (std::uint64_t)lhs.get(1, 1) * rhs.get(r, c);
                v -= (std::uint64_t)lhs.get(1, 0) * rhs.get(r - 1, c);
            }
            result.set(r, c, v % 3);
        }
    }
    return result;
}

BaseMatrix operator^(BaseMatrix mat, SizeType exponent) {
    BaseMatrix result = BaseMatrix::getIdentityMatrix(mat.getSize());
    while (exponent > 0) {
        if (exponent & 1) {
            result = result * mat;
        }
        mat = mat * mat;
        exponent >>= 1;
    }
    return result;
}

std::string solve(SizeType n, SizeType k, const std::string& s) {
    assert(n == s.size());

    ResultMatrix input;
    input.reserve(n);
    for (auto c : s) {
        if (c == 'R') {
            input.push_back(0);
        } else if (c == 'G') {
            input.push_back(1);
        } else { // c == 'W'.
            input.push_back(2);
        }
    }

    SizeType dig = 1;
    while ((1 << dig) < n * 2) {
        ++dig;
    }
    solver.initialize(1 << dig);

    BaseMatrix output(input);
    BaseMatrix mat;
    mat.fill(n);

    mat = mat ^ k;
    output = output * mat;

    std::string result;
    result.reserve(n);
    for (SizeType i = 0; i < n; ++i) {
        auto v = output.get(0, i);
        v = (v + 3) % 3;
        if (v == 0) {
            result.push_back('R');
        } else if (v == 1) {
            result.push_back('G');
        } else { // v == 2.
            result.push_back('W');
        }
    }
    return result;
}

int main() {
    // std::freopen("/Volumes/SSD-Xcode/Android/projects/mep/mepcpp/mepcpp/in",
    // "r", stdin);
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    SizeType n;
    SizeType k;
    std::string s;
    std::cin >> n >> k >> s;
    std::cout << solve(n, k, s) << std::endl;
}
