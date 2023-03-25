#ifndef __RAY_H__
#define __RAY_H__

#include <vec3.h>

struct ray {
    ray() {}
    ray(const point3 &ori, const vec3 &dir) : orig(ori), dir(dir) {}

    ray(point3 &&ori, vec3 &&dir) : orig(ori), dir(dir) {}

    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    point3 at(double t) const { return orig + t * dir; }

    point3 orig;
    vec3 dir;
};

#endif