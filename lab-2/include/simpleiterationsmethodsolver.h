#pragma once

#include "approximatesolver.h"

class SimpleIterationsMethodSolver : public ApproximateSolver
{
public:
    SimpleIterationsMethodSolver() = default;
    ~SimpleIterationsMethodSolver() = default;

    Column solve(const Matrix& A, const Column& b, const Column& x = Column(), double epsilon = 0) override;

    std::string name() const override;
};
