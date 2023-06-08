#ifndef OBJECT_H
#define OBJECT_H

#include "ray.h"

struct intersection_record {
    point3 p;
    vector normal;
    double t;
    bool front_face;
    vector color;
    vector phong;
    int phongE;
    ray r;

    inline void setPhong(vector phong){
        this->phong = phong;
    }
    inline void setPhongE(double phongE){
        this->phongE = phongE;
    }

    inline void set_face_normal(const ray& r, const vector& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class object {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, intersection_record& rec) const = 0;
};

#endif