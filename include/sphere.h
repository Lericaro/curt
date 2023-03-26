#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "ray.h"
#include <cmath>
#include <hittable.h>
#include <vec3.h>

class sphere : public hittable {
  public:
    sphere() = default;
    sphere(vec3 cen, double r, std::shared_ptr<material> m)
        : center(cen), radius(r), pmaterial(m){};

    virtual bool hit(const ray &r, double tmin, double tmax,
                     hit_record &rec) const override;

  private:
    vec3 center;
    double radius;
    std::shared_ptr<material> pmaterial;
};

inline bool sphere::hit(const ray &r, double tmin, double tmax,
                        hit_record &rec) const {
    auto oc = r.origin() - center;

    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;

    auto dis = half_b * half_b - a * c;

    if (dis > 0) {
        auto root = std::sqrt(dis);

        auto temp = (-half_b - root) / a;

        if (temp < tmax && temp > tmin) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            auto out_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, out_normal);
            rec.pmaterial = pmaterial;
            return 1;
        }

        temp = (-half_b + root) / a;

        if (temp < tmax && temp > tmin) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            auto out_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, out_normal);
            rec.pmaterial = pmaterial;
            return 1;
        }
    }

    return 0;
}

#endif