//
// Created by TianKai Ma on 2023/12/19.
//

#include "BisectMethod.h"

ull CalculateSignChange(const Vector &x, const Vector &y, lld mu) {
#ifdef DEBUG
    if (x.size != y.size + 1) {
        throw std::invalid_argument("x.size != y.size + 1");
    }
#endif

    auto n = x.size;
    auto s = 0;
    auto q = x.array[0] - mu;
    for (ull k = 0; k < n; k++) {
        if (q < 0) {
            s++;
        }
        if (k != n - 1) {
            if (q == 0) {
                q = std::abs(y.array[k]) * 1e-10;
            }

            q = x.array[k + 1] - mu - y.array[k] * y.array[k] / q;
        }
    }
    return s;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

std::vector<lld> BisectMethodCall(const Vector &x, const Vector &y, lld start, lld end, lld precision) {
#ifdef DEBUG
    if (start > end) {
        throw std::invalid_argument("start > end");
    }
    if (precision < 0) {
        throw std::invalid_argument("precision < 0");
    }
#endif

    if (end - start < precision) {
        auto l = CalculateSignChange(x, y, start);
        auto r = CalculateSignChange(x, y, end);

        if (l > r) {
            return {};
        }

        auto result = std::vector<lld>(r - l, (start + end) / 2);
        return result;
    }

    auto mid = (start + end) / 2;
    auto l = CalculateSignChange(x, y, start);
    auto r = CalculateSignChange(x, y, end);

    if (l == r) {
        return {};
    }

    auto m = CalculateSignChange(x, y, mid);
    auto result = std::vector<lld>();
    if (l != m) {
        auto left = BisectMethodCall(x, y, start, mid, precision);
        result.insert(result.end(), left.begin(), left.end());
    }
    if (m != r) {
        auto right = BisectMethodCall(x, y, mid, end, precision);
        result.insert(result.end(), right.begin(), right.end());
    }
    return result;
}

#pragma clang diagnostic pop

Vector BisectMethod(const Vector &x, const Vector &y, lld precision) {
#ifdef DEBUG
    if (x.size != y.size + 1) {
        throw std::invalid_argument("x.size != y.size + 1");
    }
    if (precision < 0) {
        throw std::invalid_argument("precision < 0");
    }
#endif

    // determine Infinity norm of T: x_n + y_n + y_(n-1)
    auto n = x.size;
    auto max = x.array[0];
    for (ull i = 1; i < n; i++) {
        lld temp;
        if (i == n - 1) {
            temp = std::abs(x.array[i]) + std::abs(y.array[i]);
        } else {
            temp = std::abs(x.array[i]) + std::abs(y.array[i - 1]) + std::abs(y.array[i]);
        }
        if (temp > max) {
            max = temp;
        }
    }

    auto l = -max;
    auto r = max;
    auto result = BisectMethodCall(x, y, l, r, precision);
    return Vector(result);
}