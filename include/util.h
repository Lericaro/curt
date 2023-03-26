#ifndef __UTIL_H__
#define __UTIL_H__

#include <cmath>
#include <functional>
#include <limits>
#include <random>
const double pi = std::acos(-1);
const double inf = std::numeric_limits<double>::infinity();

inline double degrees_to_radians(double degrees) { return degrees * pi / 180; }

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    static std::function<double()> rand_generator =
        std::bind(distribution, generator);
    return rand_generator();
}

inline double clamp(double x, double minx, double maxx) {
    if (x < minx)
        return minx;
    if (x > maxx)
        return maxx;
    return x;
}

#endif