#include "sampleequationsystem.h"

SampleEquationSystem::SampleEquationSystem()
{
    m_f1 = "y";
    m_f2 = "x";
    m_f3 = "x + 2y + 3z";
}

double SampleEquationSystem::f1(double x, double y, double z) const
{
    return y;
}

double SampleEquationSystem::f2(double x, double y, double z) const
{
    return x;
}

double SampleEquationSystem::f3(double x, double y, double z) const
{
    return x + 2 * y + 3 * z;
}
