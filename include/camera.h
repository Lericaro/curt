#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "util.h"
#include "vec3.h"
#include <cmath>
#include <math.h>
#include <ray.h>

class camera {
  public:
    camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect,
           double aperture, double foucs_dist) {

        origin = lookfrom;

        // vec3 u, v, w;
        lens_radius = aperture / 2;

        auto theta = degrees_to_radians(vfov);
        auto half_height = tan(theta / 2);
        auto half_width = aspect * half_height;

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        lower_left_corner = origin - half_width * foucs_dist * u -
                            half_height * foucs_dist * v - foucs_dist * w;

        horizontal = 2 * half_width * u * foucs_dist;
        vertical = 2 * half_height * v * foucs_dist;
    }

    ray get_ray(double s, double t) {
        auto rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();

        return ray{origin + offset, lower_left_corner + s * horizontal +
                                        t * vertical - origin - offset};
    }

  public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
};

#endif