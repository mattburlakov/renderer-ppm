#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "utility.h"

class camera {
    private:
        point origin;
        point lower_left_corner;
        vect3 horizontal;
        vect3 vertical;

    public:
        camera(point lookfrom, point lookat, vect3 vup,
            double vfov, double aspect_ratio) {

            double theta = degrees_to_radians(vfov);
            double h     = std::tan(theta/2.0);

            double viewport_height  = 2.0 * h;
            double viewport_width   = aspect_ratio * viewport_height;

            vect3 w = unit_vector(lookfrom - lookat);
            vect3 u = unit_vector(cross(vup, w));
            vect3 v = cross(w, u);

            origin        = lookfrom;
            horizontal    = viewport_width * u;
            vertical      = viewport_height * v;

            lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - w;
        }

        Ray get_ray(double s, double t) const {
            return Ray(origin, lower_left_corner + horizontal * s + vertical * t - origin);
        }
};

#endif