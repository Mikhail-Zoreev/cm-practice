#pragma once

#include <string>

#include "matrix.h"

class EquationsSystemSolver
{
public:
    EquationsSystemSolver() = default;
    virtual ~EquationsSystemSolver() = default;

    virtual Column solve(const Matrix& A, const Column& b, const Column& x, double epsilon = 0) = 0;

    virtual std::string name() const = 0;

    virtual bool approximate() const = 0;
};
