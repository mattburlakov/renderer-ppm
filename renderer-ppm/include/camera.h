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
        camera(){
            double aspect_ratio     = 16.0 / 9.0;

            double viewport_height  = 2.0;
            double viewport_width   = aspect_ratio * viewport_height;
            double focal_length     = 1.0;

            origin        = point(0, 0, 0);
            horizontal    = vect3(viewport_width, 0, 0);
            vertical      = vect3(0, viewport_height, 0);

            lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - vect3(0, 0, focal_length);
        }

        Ray get_ray(double u, double v) const {
            return Ray(origin, lower_left_corner + horizontal * u + vertical * v - origin);
        }
};

#endif