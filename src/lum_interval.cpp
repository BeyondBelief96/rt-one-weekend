#include "lum_interval.h"
#include <limits>

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

    double Interval::clamp(double t) const
    {
        if (t < min) return min;
        if (t > max) return max;
        return t;
    }

    const Interval Interval::empty = Interval(std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
    const Interval Interval::universe = Interval(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
}