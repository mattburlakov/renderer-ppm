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
        vect3 u, v, w;

        double lens_radius;

    public:
        camera(point lookfrom, point lookat, vect3 vup,
            double vfov, double aspect_ratio,
            double aperture, double focus_distance) {

            double theta = degrees_to_radians(vfov);
            double h     = std::tan(theta/2.0);

            double viewport_height  = 2.0 * h;
            double viewport_width   = aspect_ratio * viewport_height;

            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            origin        = lookfrom;
            horizontal    = focus_distance * viewport_width * u;
            vertical      = focus_distance * viewport_height * v;

            lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - focus_distance * w;

            lens_radius = aperture / 2.0;
        }

        Ray get_ray(double s, double t) const {
            vect3 rd = lens_radius * random_in_unit_disk();
            vect3 offset = u * rd.x() + v * rd.y();

            return Ray(origin + offset,
                lower_left_corner + horizontal * s + vertical * t - origin - offset);
        }
};

#endif