#pragma once

#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

struct hit_record {
    point p;
    vect3 normal;
    double t = 0;

    bool front_face = false;

    inline void set_face_normal(const Ray& r, const vect3& outward_normal){
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : vect3(1.0, 0, 0); //mark inside as red
    }
};

class hittable{
    public:
        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif