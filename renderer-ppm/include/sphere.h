#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vect3.h"

class sphere : public hittable{
    public:
        point center;
        double radius = 0;

    sphere(){}
    sphere(point c, double r) : center(c), radius(r){}

    bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override{
        vect3 sc = std::move(r.origin() - center);

        double a = r.direction().length_squared();
        double hb = dot(sc, r.direction());
        double c = sc.length_squared() - radius * radius;

        double discriminant = hb * hb - a * c;

        if (discriminant < 0) return false;
        double sqd = std::sqrt(discriminant);

        double root = (-hb - sqd) / a;
        if (root < t_min || t_max < root){
            root = (-hb + sqd) / a;
            if (root < t_min || t_max < root)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vect3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }
};

#endif