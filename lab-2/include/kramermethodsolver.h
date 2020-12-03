#pragma once

#include "accuratesolver.h"

#include <stdexcept>

class KramerMethodSolver : public AccurateSolver
{
public:
    KramerMethodSolver() = default;
    ~KramerMethodSolver() = default;

    Column solve(const Matrix& A, const Column& b, const Column& x = Column(), double epsilon = 0) override;
};
