#pragma once

#include <cmath>
#include <iostream>

class vect3 {
public:
	double data[3];
	vect3() : data{0, 0, 0} {}
	vect3(double d1, double d2, double d3) : data{ d1, d2, d3 } {}

	double x() { return data[0]; }
	double y() { return data[1]; }
	double z() { return data[2]; }

	vect3 operator- () const { return vect3(-data[0], -data[1], -data[2]); }
};