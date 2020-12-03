#pragma once

#include "accuratesolver.h"

class LUDecompositionMethodSolver : public AccurateSolver
{
public:
    LUDecompositionMethodSolver() = default;
    ~LUDecompositionMethodSolver() = default;

    Column solve(const Matrix& A, const Column& b, const Column& x = Column(), double epsilon = 0) override;

    std::string name() const override;
};
