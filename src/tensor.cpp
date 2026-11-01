#include "ktorch/tensor.hpp"

#include <stdexcept>

namespace ktorch {

// TODO(S1): 实现构造函数、rows()、cols()、size()。
// TODO(S2): 实现 at() 与 data()，包括越界检查。
//
// 提示：
//   - 构造函数里用 std::vector<double>(rows * cols, init) 初始化 data_。
//   - rows_/cols_ 先保存再构造 data_，顺序会影响初始化列表。
//   - 越界检查用 i >= rows_ || j >= cols_。

Tensor::Tensor(std::size_t rows, std::size_t cols, double init) : rows_(rows),cols_(cols),data_(rows*cols,init) {
    if (rows_ == 0 || cols_ == 0) {
        throw std::invalid_argument("Tensor: rows and cols must be positive");
    }
    // data_.resize(rows_*cols_);
    // for(size_t i=0;i<data_.size();i++)
    //     data_[i]=init;
    //throw std::logic_error("TODO(S1): implement Tensor(rows, cols, init)");
}

std::size_t Tensor::rows() const {
    return rows_;
    //throw std::logic_error("TODO(S1): implement rows()");
}

std::size_t Tensor::cols() const {
    return cols_;
    //throw std::logic_error("TODO(S1): implement cols()");
}

std::size_t Tensor::size() const {
    return rows_*cols_;
    //throw std::logic_error("TODO(S1): implement size()");
}

double& Tensor::at(std::size_t i, std::size_t j) {
    return const_cast<double&>(static_cast<const Tensor&>(*this).at(i, j));
    //throw std::logic_error("TODO(S2): implement at(i, j)");
}

const double& Tensor::at(std::size_t i, std::size_t j) const {
    if(i>=rows_||j>=cols_)
        throw std::out_of_range("Tensor::at: index out of range");
    return data_[i*cols_+j];
    //throw std::logic_error("TODO(S2): implement at(i, j) const");
}

std::vector<double>& Tensor::data() {
    return data_;
    //throw std::logic_error("TODO(S2): implement data()");
}

const std::vector<double>& Tensor::data() const {
    return data_;
    //throw std::logic_error("TODO(S2): implement data() const");
}

}  // namespace ktorch
