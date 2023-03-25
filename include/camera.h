#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <ray.h>

class camera {
  public:
    camera() {
        lower_left_corner = {-2, -1, -1};
        horizonral = {4, 0, 0};
        vertical = {0, 2, 0};
        origin = {0, 0, 0};
    }

    ray get_ray(double u, double v) {
        return ray{origin,
                   lower_left_corner + u * horizonral + v * vertical - origin};
    }

  public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizonral;
    vec3 vertical;
};

#endif