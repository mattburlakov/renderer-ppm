#pragma once

#ifndef RAY_H
#define RAY_H

#include "vect3.h"

class Ray {
public:
	point orig;
	vect3 dir;

	Ray(){}
	Ray(const point& origin, const vect3& direction) : orig(origin), dir(direction) {}

	point origin() const { return orig; }
	point direction() const { return dir; }

	point at(double t) const { return orig + dir*t; }
};

#endif