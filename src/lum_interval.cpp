#include "lum_interval.h"

namespace Lumina
{
    Interval::Interval() : min(0), max(0) {};

    Interval::Interval(double min, double max) : min(min), max(max) {};

    double Interval::getMin() const
    {
        return min;
    }

    double Interval::getMax() const
    {
        return max;
    }

    double Interval::size() const
    {
        return max - min;
    }

    bool Interval::contains(double t) const
    {
        return min <= t && t <= max;
    }

    const Interval Interval::empty = Interval(infinity, -infinity);
    const Interval Interval::universe = Interval(-infinity, infinity);
}