#pragma once

#include "equationssystemsolver.h"

class ApproximateSolver : public EquationsSystemSolver
{
public:
    ApproximateSolver() = default;
    ~ApproximateSolver() = default;

    bool approximate() const override;
};
