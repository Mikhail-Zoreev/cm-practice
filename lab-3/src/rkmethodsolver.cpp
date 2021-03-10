#include "rkmethodsolver.h"

#include <stdexcept>

RKMethodSolver::RKMethodSolver(AbstractEquationSystem *system)
{
    p_system = system;
}

std::vector<std::array<double, 4>> RKMethodSolver::solve(double a, double b, int steps,
                                                         const std::array<double, 3>& initial_conditions)
{
    if (steps <= 0)
    {
        throw std::runtime_error("Count of iterations must be greater than zero");
    }
    if (b <= a)
    {
        throw std::runtime_error("Ending point must be greater than starting point");
    }

    double h = (b - a) / steps;
    double t = a + h;

    std::vector<std::array<double, 4>> result;
    std::array<std::array<double, 4>, 3> K;
    double x_previous = initial_conditions[0];
    double y_previous = initial_conditions[1];
    double z_previous = initial_conditions[2];
    double x, y, z;

    for (int i = 1; i <= steps; i++)
    {
        K[0][0] = h * p_system->f1(x_previous, y_previous, z_previous);
        K[1][0] = h * p_system->f2(x_previous, y_previous, z_previous);
        K[2][0] = h * p_system->f3(x_previous, y_previous, z_previous);

        K[0][1] = h * p_system->f1(x_previous + K[0][0] / 2, y_previous + K[1][0] / 2, z_previous + K[2][0] / 2);
        K[1][1] = h * p_system->f2(x_previous + K[0][0] / 2, y_previous + K[1][0] / 2, z_previous + K[2][0] / 2);
        K[2][1] = h * p_system->f3(x_previous + K[0][0] / 2, y_previous + K[1][0] / 2, z_previous + K[2][0] / 2);

        K[0][2] = h * p_system->f1(x_previous + K[0][1] / 2, y_previous + K[1][1] / 2, z_previous + K[2][1] / 2);
        K[1][2] = h * p_system->f2(x_previous + K[0][1] / 2, y_previous + K[1][1] / 2, z_previous + K[2][1] / 2);
        K[2][2] = h * p_system->f3(x_previous + K[0][1] / 2, y_previous + K[1][1] / 2, z_previous + K[2][1] / 2);

        K[0][3] = h * p_system->f1(x_previous + K[0][2], y_previous + K[1][2], z_previous + K[2][2]);
        K[1][3] = h * p_system->f2(x_previous + K[0][2], y_previous + K[1][2], z_previous + K[2][2]);
        K[2][3] = h * p_system->f3(x_previous + K[0][2], y_previous + K[1][2], z_previous + K[2][2]);

        x = x_previous + (K[0][0] + 2 * K[0][1] + 2 * K[0][2] + K[0][3]) / 6;
        y = y_previous + (K[1][0] + 2 * K[1][1] + 2 * K[1][2] + K[1][3]) / 6;
        z = z_previous + (K[2][0] + 2 * K[2][1] + 2 * K[2][2] + K[2][3]) / 6;

        result.push_back({x, y, z ,t});
        t += h;

        x_previous = x;
        y_previous = y;
        z_previous = z;
    }

    return result;
}
