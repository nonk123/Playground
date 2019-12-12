#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>

namespace Playground::Utils {
    template<typename T = float>
    const T pi = std::acos(-T(1));

    template<typename T = float>
    const T radToDeg = T(180.0) / pi<T>;

    template<typename T = float>
    const T degToRad = pi<T> / T(180.0);
}

#endif
