#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "utility.h"

struct hit_record;

class material {
    public:
        virtual bool scatter(const Ray& r_in, const hit_record& rec,
                             color& attenuation, Ray& scattered) const = 0;
};

class lambertian : public material {
    public:
        color albedo;

        lambertian(const color& a) : albedo(a) {}

        virtual bool scatter(const Ray& r_in, const hit_record& rec,
                             color& attenuation, Ray& scattered) const override {

            vect3 scatter_direction = rec.normal + random_unit_vector();

            if (scatter_direction.near_zero()) scatter_direction = rec.normal;

            scattered   = Ray(rec.p, scatter_direction);
            attenuation = albedo;
            
            return true;
        }
};

class metal : public material{
    public:
        color albedo;
        double fuzz;

        metal(const color& a, double f) : albedo(a), fuzz(f) {}

        virtual bool scatter(const Ray &r_in, const hit_record &rec,
                            color &attenuation, Ray &scattered) const override {

            vect3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);

            scattered       = Ray(rec.p,  + fuzz*random_in_unit_sphere());
            attenuation     = albedo;
            
            return (dot(scattered.direction(), rec.normal) > 0);
        }
};

#endif