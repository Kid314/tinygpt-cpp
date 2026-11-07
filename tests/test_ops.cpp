// S3 add / S4 matmul 的测试（由 AI 编写，用户负责实现）。
//
// 运行（项目根目录）：
//   powershell -ExecutionPolicy Bypass -File scripts/build.ps1 -Test tests/test_ops.cpp
//
// 覆盖：
//   1. 2x3 同形状相加，手算结果；
//   2. 结果形状正确，且没有修改输入 a/b；
//   3. 形状不一致时抛 std::invalid_argument；
//   4. 1x1 最小情况。
//   5. matmul：3x3、非方阵、行列向量、负数小数、尺寸错误和输入独立性。

#include "ktorch/ops.hpp"

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <vector>

namespace {

void check(bool ok, const char* what) {
    if (!ok) {
        std::fprintf(stderr, "FAIL: %s\n", what);
        std::exit(1);
    }
}

void check_matrix(const ktorch::Tensor& actual, std::size_t rows,
                  std::size_t cols, const std::vector<double>& expected,
                  const char* what) {
    check(actual.rows() == rows && actual.cols() == cols, what);
    check(actual.size() == expected.size(), what);
    for (std::size_t i = 0; i < expected.size(); ++i) {
        if (!(std::fabs(actual.data()[i] - expected[i]) < 1e-12)) {
            std::fprintf(stderr, "FAIL: %s at (%zu, %zu): expected %.17g, got %.17g\n",
                         what, i / cols, i % cols, expected[i], actual.data()[i]);
            std::exit(1);
        }
    }
}

void test_matmul() {
    // 1) 对话中的 3x3 手算例子，检查全部九个元素。
    ktorch::Tensor a(3, 3);
    ktorch::Tensor b(3, 3);
    a.data() = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    b.data() = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    const auto original_a = a.data();
    const auto original_b = b.data();
    auto c = ktorch::matmul(a, b);
    check_matrix(c, 3, 3, {30, 24, 18, 84, 69, 54, 138, 114, 90},
                 "matmul 3x3");
    check(a.data() == original_a && b.data() == original_b,
          "matmul preserves every input element");
    c.at(0, 0) = -999;
    check(a.data() == original_a && b.data() == original_b,
          "matmul result does not alias either input");

    // 2) 2x3 @ 3x2：共同维度为 3，结果为 2x2。
    ktorch::Tensor left(2, 3);
    ktorch::Tensor right(3, 2);
    left.data() = {1, 2, 3, 4, 5, 6};
    right.data() = {7, 8, 9, 10, 11, 12};
    check_matrix(ktorch::matmul(left, right), 2, 2, {58, 64, 139, 154},
                 "matmul 2x3 @ 3x2");

    // 3) M、N、K 各不相同，避免方形输出掩盖循环上界错误。
    ktorch::Tensor wide(3, 4);
    wide.data() = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    check_matrix(ktorch::matmul(left, wide), 2, 4,
                 {38, 44, 50, 56, 83, 98, 113, 128},
                 "matmul 2x3 @ 3x4");

    // 4) 1x1，保留负数和小数。
    check_matrix(ktorch::matmul(ktorch::Tensor(1, 1, -1.5),
                               ktorch::Tensor(1, 1, 2.0)),
                 1, 1, {-3.0}, "matmul 1x1");

    // 5) 行向量乘列向量：包含零、小数和正负项抵消。
    ktorch::Tensor row(1, 3);
    ktorch::Tensor col(3, 1);
    row.data() = {-1.5, 0, 2};
    col.data() = {2, -4, 1.5};
    check_matrix(ktorch::matmul(row, col), 1, 1, {0}, "matmul dot product");

    // 6) 列向量乘行向量：共同维度 K=1，输出 3x3。
    check_matrix(ktorch::matmul(col, row), 3, 3,
                 {-3, 0, 4, 6, 0, -8, -2.25, 0, 3},
                 "matmul outer product");

    // 7) 两个 2x3 虽然同形状，却不能矩阵相乘。
    bool threw = false;
    try {
        (void)ktorch::matmul(left, left);
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    check(threw, "matmul incompatible inner dimensions throw invalid_argument");
    std::printf("PASS: matmul (7 cases)\n");
}

}  // namespace

int main() {
    try {
        // 1) 2x3 同形状相加
        ktorch::Tensor a(2, 3);
        ktorch::Tensor b(2, 3);
        const double av[2][3] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
        const double bv[2][3] = {{10.0, 20.0, 30.0}, {40.0, 50.0, 60.0}};
        const double expected[2][3] = {{11.0, 22.0, 33.0}, {44.0, 55.0, 66.0}};
        for (std::size_t i = 0; i < 2; ++i) {
            for (std::size_t j = 0; j < 3; ++j) {
                a.at(i, j) = av[i][j];
                b.at(i, j) = bv[i][j];
            }
        }

        ktorch::Tensor c = ktorch::add(a, b);
        check(c.rows() == 2, "result rows == 2");
        check(c.cols() == 3, "result cols == 3");
        check(c.size() == 6, "result size == 6");
        for (std::size_t i = 0; i < 2; ++i) {
            for (std::size_t j = 0; j < 3; ++j) {
                check(c.at(i, j) == expected[i][j], "add result matches hand calculation");
            }
        }

        // 2) 输入不能被修改
        check(a.at(0, 0) == 1.0, "a is not modified");
        check(b.at(0, 0) == 10.0, "b is not modified");

        // 3) 结果必须是新对象，不是 a/b 的别名
        c.at(0, 0) = -1.0;
        check(a.at(0, 0) == 1.0, "result does not alias input a");

        // 4) 形状不一致必须抛 std::invalid_argument
        ktorch::Tensor d(2, 3);
        ktorch::Tensor e(3, 2);
        bool threw = false;
        try {
            (void)ktorch::add(d, e);
        } catch (const std::invalid_argument&) {
            threw = true;
        } catch (...) {
            // 抛了其他异常也算失败
        }
        check(threw, "shape mismatch throws std::invalid_argument");

        // 5) 1x1 最小情况
        ktorch::Tensor one(1, 1, 2.0);
        ktorch::Tensor two(1, 1, 3.0);
        ktorch::Tensor five = ktorch::add(one, two);
        check(five.at(0, 0) == 5.0, "1x1 add");

        test_matmul();
        std::printf("PASS: ops\n");
        return 0;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "ERROR: %s\n", e.what());
        return 1;
    }
}
