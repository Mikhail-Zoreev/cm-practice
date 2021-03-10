#pragma once

#include "approximatesolver.h"

#include <random>

class SeidelMethodSolver : public ApproximateSolver
{
public:
    SeidelMethodSolver() = default;
    ~SeidelMethodSolver() = default;

    Column solve(const Matrix& A, const Column& b, const Column& x = Column(), double epsilon = 0) override;

    std::string name() const override;
};
