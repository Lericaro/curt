#ifndef __HITABLE_H__
#define __HITABLE_H__

#include "vec3.h"
#include <ray.h>
struct hit_record {
    vec3 p;
    vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const ray &r, const vec3 &out_normal) {
        front_face = dot(r.direction(), out_normal) < 0;
        normal = front_face ? out_normal : -out_normal;
    }
};

class hittable {
  public:
    virtual bool hit(const ray &r, double t_min, double t_max,
                     hit_record &rec) const = 0;
};
 
#endif