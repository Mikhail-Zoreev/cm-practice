#pragma once

#include "accuratesolver.h"

class GaussMethodSolver : public AccurateSolver
{
public:
    GaussMethodSolver() = default;
    ~GaussMethodSolver() = default;

    Column solve(const Matrix& A, const Column& b, const Column& x = Column(), double epsilon = 0) override;

    std::string name() const override;
};
