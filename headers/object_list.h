#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

#include "object.h"
#include "color.h"
#include "sphere_object.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class object_list : public object {
    public:
        object_list() {}
        object_list(shared_ptr<object> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<object> object) { objects.push_back(object); }

        virtual bool hit(
            const ray& r, double t_min, double t_max, intersection_record& rec) const override;

    public:
        std::vector<shared_ptr<object>> objects;
};

bool object_list::hit(const ray& r, double t_min, double t_max, intersection_record& rec) const {
    intersection_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif