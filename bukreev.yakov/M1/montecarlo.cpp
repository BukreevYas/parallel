#include "montecarlo.hpp"
#include <algorithm>
#include <iostream>
#include <limits>

namespace bukreev
{
    struct BoundingBox
    {
        constexpr static int init = std::numeric_limits< int >::max();
        BoundingBox(): left(init), right(init), top(init), bottom(init) {}
        int left;
        int right;
        int top;
        int bottom;
    };
}

bukreev::AreaResult bukreev::monteCarlo(const std::vector< Figure >& figures)
{
    BoundingBox box;
    for (const Figure& f : figures) {
        box.left = std::min(box.left, f.cx - f.r);
        box.bottom = std::min(box.bottom, f.cy - f.r);
        box.right = std::max(box.right, f.cx + f.r);
        box.top = std::max(box.top, f.cy + f.r);
    }
    return {};
}
