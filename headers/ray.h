#ifndef RAY_H
#define RAY_H

#include "vector.h"

class ray {
    public:
        ray() {}
        ray(const point3& origin, const vector& direction)
            : orig(origin), dir(direction)
        {}

        point3 origin() const  { return orig; }
        vector direction() const { return dir; }

        point3 at(double t) const {
            return orig + t*dir;
        }

    public:
        point3 orig;
        vector dir;
};

#endif