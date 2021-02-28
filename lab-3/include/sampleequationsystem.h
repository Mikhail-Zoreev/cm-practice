#pragma once

#include "abstractequationsystem.h"

class SampleEquationSystem : public AbstractEquationSystem
{
public:
    SampleEquationSystem();
    ~SampleEquationSystem() = default;

    virtual double f1(double x, double y, double z) const override;
    virtual double f2(double x, double y, double z) const override;
    virtual double f3(double x, double y, double z) const override;
};
