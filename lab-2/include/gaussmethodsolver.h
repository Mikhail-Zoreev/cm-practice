#pragma once

#include "equationssystemsolver.h"

class GaussMethodSolver : public EquationsSystemSolver
{
public:
    GaussMethodSolver() = default;
    ~GaussMethodSolver() = default;

    Column solve(const Matrix& A, const Column& b, double epsilon = 0) override;
};
