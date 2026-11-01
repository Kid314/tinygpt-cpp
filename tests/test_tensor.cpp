// 第一个测试：Tensor 的存储、形状与元素访问。
//
// 运行方式（在项目根目录）：
//   powershell -ExecutionPolicy Bypass -File scripts/build.ps1
//
// 测试会先失败并提示 TODO；实现 src/tensor.cpp 后应输出 PASS。

#include "ktorch/tensor.hpp"

#include <cstdio>
#include <cstdlib>
#include <exception>

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
        ktorch::Tensor t(2, 3);
        check(t.rows() == 2, "rows() == 2");
        check(t.cols() == 3, "cols() == 3");
        check(t.size() == 6, "size() == 6");
        check(t.at(0, 0) == 0.0, "initial value is 0.0");

        // 行优先：A[1,2] 是第 1*3+2 = 5 个元素。
        t.at(1, 2) = 6.0;
        check(t.data()[5] == 6.0, "row-major offset(1,2) == 5");

        ktorch::Tensor filled(2, 2, 2.5);
        check(filled.at(0, 0) == 2.5, "init value at (0,0)");
        check(filled.at(1, 1) == 2.5, "init value at (1,1)");

        std::printf("PASS: tensor\n");
        return 0;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "ERROR: %s\n", e.what());
        return 1;
    }
}
