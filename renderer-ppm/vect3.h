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

	double  operator[](int i) const { return data[i]; }
	double& operator[](int i)		{ return data[i]; }

	double length() const { 
		return std::sqrt(pow(data[0], 2) + 
						 pow(data[1], 2) +
						 pow(data[2], 2)); 
	}
};

vect3& operator+(const vect3& vA, const vect3& vB) {
	vect3 vC(vA.data[0] + vB.data[0],
			 vA.data[1] + vB.data[1],
			 vA.data[2] + vB.data[2]);
	return vC;
}

vect3& operator-(const vect3& vA, const vect3& vB) {
	vect3 vC(vA.data[0] - vB.data[0],
			 vA.data[1] - vB.data[1],
			 vA.data[2] - vB.data[2]);
	return vC;
}

vect3& operator*(const vect3& vA, const int k) {
	vect3 vC(vA.data[0] * k,
		vA.data[1] * k,
		vA.data[2] * k);
	return vC;
}

vect3& operator/(const vect3& vA, const int k) {
	vect3 vC(vA.data[0] / k,
			 vA.data[1] / k,
			 vA.data[2] / k);
	return vC;
}

using point = vect3;
using color	= vect3;