#include "sampleaccuratesolution.h"

SampleAccurateSolution::SampleAccurateSolution(double t_from, const std::array<double, 3>& initial_conditions)
{
    c2 = (initial_conditions[0] + initial_conditions[1]) / (-4) * 3 / std::exp(t_from);
    c1 = (initial_conditions[0] - initial_conditions[1]) / 8 / std::exp(-t_from);

    c3 = (initial_conditions[2] - c1 * std::exp(-t_from) - c2 * std::exp(t_from)) / std::exp(3 * t_from);

    m_f1 = "4" + QString::number(c1, 'g', 2) + "e<sup>-t</sup> + (-2/3 * " + QString::number(c2, 'g', 2) + ") * e<sup>t</sup>";
    m_f2 = "-4" + QString::number(c1, 'g', 2) + "e<sup>-t</sup> + (-2/3 * " + QString::number(c2, 'g', 2) + ") * e<sup>t</sup>";
    m_f3 = QString::number(c1, 'g', 2) + "e<sup>-t</sup> + " + QString::number(c2, 'g', 2) + "e<sup>t</sup> + " + QString::number(c3, 'g', 2) + "e<sup>3t</sup>";;
}

double SampleAccurateSolution::f1(double t) const
{
    return 4 * c1 * std::exp(-t) - 2 * c2 * std::exp(t) / 3;
}

double SampleAccurateSolution::f2(double t) const
{
    return -4 * c1 * std::exp(-t) - 2 * c2 * std::exp(t) / 3;
}

double SampleAccurateSolution::f3(double t) const
{
    return c1 * std::exp(-t) + c2 * std::exp(t) + c3 * std::exp(3 * t);
}
