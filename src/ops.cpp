#include "ktorch/ops.hpp"
#include <cstddef>
#include <stdexcept>
namespace ktorch {

Tensor add(const Tensor& a, const Tensor& b)//两个矩阵相加
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

Tensor matmul(const Tensor& a, const Tensor& b)//两个矩阵相乘
{
    const std::size_t is_cols=a.cols();
    const std::size_t is_rows=b.rows();
    const std::size_t t_cols=b.cols();
    const std::size_t t_rows=a.rows();
    if(is_cols==is_rows)
    {
        Tensor temp(t_rows,t_cols);
        for(std::size_t i=0;i<t_rows;i++)
        {
            for(std::size_t j=0;j<t_cols;j++)
            {
                for(std::size_t k=0;k<is_cols;k++)
                {
                    temp.at(i,j)+=a.at(i,k)*b.at(k,j);
                }
            }
        }
        return temp;
    }
    else
        throw std::invalid_argument("matmul: shape mismatch");
};

}