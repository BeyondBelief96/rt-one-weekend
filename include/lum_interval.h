#pragma once

namespace Lumina
{
  class Interval
  {
    public:
      Interval();
      Interval(double min, double max);
      double getMin() const;
      double getMax() const;
      double size() const;
      bool contains(double t) const;
      double clamp(double t) const;

      static const Interval empty, universe;

    private:
        double min, max;
  };
}