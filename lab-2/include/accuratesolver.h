#pragma once

#include "equationssystemsolver.h"

class AccurateSolver : public EquationsSystemSolver
{
public:
    AccurateSolver() = default;
    ~AccurateSolver() = default;

    bool approximate() const override;
};
