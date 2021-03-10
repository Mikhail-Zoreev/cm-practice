#pragma once

#include "abstractaccuratesolution.h"

#include <array>
#include <cmath>

class SampleAccurateSolution : public AbstractAccurateSolution
{
    double c1;
    double c2;
    double c3;

public:
    SampleAccurateSolution(double t_from, const std::array<double, 3>& initial_conditions);
    ~SampleAccurateSolution() = default;

    virtual double f1(double t) const;
    virtual double f2(double t) const;
    virtual double f3(double t) const;
};
