#pragma once

#include "approximatesolver.h"

#include <random>

class UpperRelaxationMethodSolver : public ApproximateSolver
{
public:
    UpperRelaxationMethodSolver() = default;
    ~UpperRelaxationMethodSolver() = default;

    Column solve(const Matrix& A, const Column& b, const Column& x = Column(), double epsilon = 0) override;
};
