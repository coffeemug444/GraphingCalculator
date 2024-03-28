#pragma once

#include <complex>

using complex = std::complex<double>;

class ASTNode
{
public:
   virtual complex evaluate(complex x) const = 0;
};
