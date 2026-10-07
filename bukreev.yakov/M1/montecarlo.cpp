#include "montecarlo.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <random>

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

    void monteCarloWorker(
        const std::vector< Figure >& figures,
        BoundingBox box,
        size_t tries, size_t seed,
        AreaResult& res
    );

    bool isInside(double x, double y, Figure f);
}

bukreev::AreaResult bukreev::monteCarlo(const std::vector< Figure >& figures)
{
    BoundingBox box;
    for (const Figure& f : figures)
    {
        box.left = std::min(box.left, f.cx - f.r);
        box.bottom = std::min(box.bottom, f.cy - f.r);
        box.right = std::max(box.right, f.cx + f.r);
        box.top = std::max(box.top, f.cy + f.r);
    }
    return {};
}

void bukreev::monteCarloWorker(
    const std::vector< Figure >& figures,
    BoundingBox box,
    size_t tries, size_t seed,
    AreaResult& res
)
{
    std::default_random_engine gen(seed);
    std::uniform_real_distribution< double > xdist(box.left, box.right);
    std::uniform_real_distribution< double > ydist(box.bottom, box.top);

    size_t total = 0;
    size_t intersect = 0;
    for (size_t i = 0; i < tries; i++)
    {
        double x = xdist(gen);
        double y = ydist(gen);
        bool inside = false;
        bool insideIntersect = true;
        for (const Figure& f : figures)
        {
            inside = inside || isInside(x, y, f);
            insideIntersect = insideIntersect && isInside(x, y, f);
        }

        total += inside ? 1 : 0;
        intersect += insideIntersect ? 1 : 0;
    }

    res.total = double(total) / double(tries);
    res.intersection = double(intersect) / double(tries);
}

bool bukreev::isInside(double x, double y, Figure f)
{
    double dx = x - f.cx;
    double dy = y - f.cy;
    return dx * dx + dy * dy < f.r * f.r;
}
