#include "cdef_function.h"
#include <boost/math/quadrature/trapezoidal.hpp>


double boostIntegral2(const std::function<double(double, double)>& func,
    double x_min, double x_max,
    double y_min, double y_max,
    const double tolerance)
{
    auto boostOuterIntegral = [&](double x) {
        return boostInnerIntegral(func, x, y_min, y_max, tolerance);
        };

    return boost::math::quadrature::trapezoidal(boostOuterIntegral, x_min, x_max, tolerance);
}


double boostInnerIntegral(const std::function<double(double, double)>& func,
    double x, double y_min, double y_max,
    const double tolerance)
{
    return boost::math::quadrature::trapezoidal(
        [&](double y) { return func(x, y); }, 
        y_min, y_max, tolerance);
}