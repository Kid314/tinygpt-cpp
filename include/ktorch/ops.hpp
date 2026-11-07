#pragma once
#include "tensor.hpp"
namespace ktorch {

Tensor add(const Tensor& a, const Tensor& b);
Tensor matmul(const Tensor& a, const Tensor& b);

}