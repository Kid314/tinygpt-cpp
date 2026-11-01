#include "ktorch/ops.hpp"
#include <cstddef>
#include <stdexcept>
namespace ktorch {

Tensor add(const Tensor& a, const Tensor& b)
{
    const std::size_t t_rows=a.rows();
    const std::size_t t_cols=a.cols();
    if(t_rows!=b.rows()||t_cols!=b.cols())
        throw std::invalid_argument("add: shape mismatch");
    Tensor temp(t_rows,t_cols);
    for(std::size_t i=0;i<t_rows;i++)
    {
        for(std::size_t j=0;j<t_cols;j++)
        {
            temp.at(i,j)=a.at(i,j)+b.at(i,j);
        }
    }
    return temp;
};

}