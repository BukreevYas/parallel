#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP

#include <vector>

namespace bukreev
{
    struct Figure
    {
        int r;
        int cx, cy;
    };

    struct AreaResult
    {
        double total;
        double intersection;
    };

    AreaResult monteCarlo(const std::vector< Figure >& figures);
}

#endif
