// S3：逐元素 add 的测试（由 AI 编写，用户负责实现）。
//
// 运行（项目根目录）：
//   powershell -ExecutionPolicy Bypass -File scripts/build.ps1 -Test tests/test_ops.cpp
//
// 覆盖：
//   1. 2x3 同形状相加，手算结果；
//   2. 结果形状正确，且没有修改输入 a/b；
//   3. 形状不一致时抛 std::invalid_argument；
//   4. 1x1 最小情况。

#include "ktorch/ops.hpp"

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <stdexcept>

namespace {

void check(bool ok, const char* what) {
    if (!ok) {
        std::fprintf(stderr, "FAIL: %s\n", what);
        std::exit(1);
    }
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

        std::printf("PASS: ops\n");
        return 0;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "ERROR: %s\n", e.what());
        return 1;
    }
}
