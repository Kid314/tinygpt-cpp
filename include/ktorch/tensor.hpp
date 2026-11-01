#pragma once

#include <cstddef>
#include <vector>

namespace ktorch {

// 二维、连续存储的 double Tensor。
//
// 约定：
//   - 行优先存储，offset(i, j) = i * cols + j
//   - data().size() == rows * cols
//   - 第一版不做 view/stride，所有 Tensor 拥有自己的数据
class Tensor {
public:
    Tensor() = default;

    // 构造 rows x cols 的矩阵，所有元素初始化为 init。
    // rows 或 cols 为 0 时抛出 std::invalid_argument。
    Tensor(std::size_t rows, std::size_t cols, double init = 0.0);

    std::size_t rows() const;
    std::size_t cols() const;
    std::size_t size() const;

    // 访问第 (i, j) 个元素；越界抛出 std::out_of_range。
    double& at(std::size_t i, std::size_t j);
    const double& at(std::size_t i, std::size_t j) const;

    std::vector<double>& data();
    const std::vector<double>& data() const;

private:
    std::size_t rows_ = 0;
    std::size_t cols_ = 0;
    std::vector<double> data_;
};

}  // namespace ktorch
