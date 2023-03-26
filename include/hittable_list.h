#ifndef __HITTABLE_LIST_H__
#define __HITTABLE_LIST_H__

#include <hittable.h>
#include <memory>
#include <vector>

class hittable_list : public hittable {
  public:
    hittable_list() = default;
    hittable_list(std::shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(std::shared_ptr<hittable> object) { objects.push_back(object); }
    virtual bool hit(const ray &r, double tmin, double tmax,
                     hit_record &rec) const override;
    std::vector<std::shared_ptr<hittable>> objects;
};

inline bool hittable_list::hit(const ray &r, double tmin, double tmax,
                               hit_record &rec) const {
    hit_record temp_rec;
    bool hit_anything = 0;
    auto closest_so_far = tmax;

    for (auto &&object : objects) {
        if (object->hit(r, tmin, closest_so_far, temp_rec)) {
            hit_anything = 1;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif