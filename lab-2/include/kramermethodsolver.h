#pragma once

#include "equationssystemsolver.h"

#include <stdexcept>

class KramerMethodSolver : public EquationsSystemSolver
{
public:
    KramerMethodSolver() = default;
    ~KramerMethodSolver() = default;

    Column solve(const Matrix& A, const Column& b, double epsilon = 0) override;
};
