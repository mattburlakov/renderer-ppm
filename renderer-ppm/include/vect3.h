#pragma once

#ifndef VECT3_H
#define VECT3_H

#include <cmath>
#include <iostream>

class vect3 {
public:
	double data[3];

	vect3() : data{0, 0, 0} {}
	vect3(double d1, double d2, double d3) : data{ d1, d2, d3 } {}

	vect3(const vect3& v) : data{v.data[0], v.data[1], v.data[2]} {} //cpy
	vect3(const vect3&& v) : data{std::move(v.data[0]), std::move(v.data[1]), std::move(v.data[2])} {} //mov

	vect3& operator=(const vect3& v){
		data[0] = std::move(v.data[0]);
		data[1] = std::move(v.data[1]);
		data[2] = std::move(v.data[2]);

		return *this;
	}

	double x() { return data[0]; }
	double y() { return data[1]; }
	double z() { return data[2]; }

	vect3 operator- () const { return vect3(-data[0], -data[1], -data[2]); }

	double  operator[](int i) const { return data[i]; }
	double& operator[](int i)		{ return data[i]; }

	double length() const {
		return std::sqrt(length());
		
	}

	double length_squared() const {
		return pow(data[0], 2) +
			   pow(data[1], 2) +
			   pow(data[2], 2);
	}

	void print(){ //debug, remove
		std::cout << data[0] << ' ' << data[1] << ' '<< data[2] << '\n';
	}
};

inline vect3 operator+(const vect3& vA, const vect3& vB) {
	return vect3 (vA.data[0] + vB.data[0],
				  vA.data[1] + vB.data[1],
				  vA.data[2] + vB.data[2]);
}

inline vect3 operator-(const vect3& vA, const vect3& vB) {
	return vect3(vA.data[0] - vB.data[0],
				 vA.data[1] - vB.data[1],
				 vA.data[2] - vB.data[2]);
}

inline vect3 operator*(const vect3& vA, double k) {
	return vect3(vA.data[0] * k,
				 vA.data[1] * k,
				 vA.data[2] * k);
}
inline vect3 operator*(double k, const vect3 &vA){
	return vect3(k * vA.data[0],
				 k * vA.data[1],
				 k * vA.data[2]);
}

inline vect3 operator/(const vect3& vA, double k) {
	return vect3 (vA.data[0] / k,
				  vA.data[1] / k,
				  vA.data[2] / k);
}

inline double dot(const vect3 &vA, const vect3 &vB){
	return (vA.data[0] * vB.data[0] +
			vA.data[1] * vB.data[1] +
			vA.data[2] * vB.data[2]);
}

inline vect3 cross(const vect3 &vA, const vect3 &vB){
	return vect3(vA.data[1] * vB.data[2] - vA.data[2] * vB.data[1],
				 vA.data[2] * vB.data[0] - vA.data[0] * vB.data[2],
				 vA.data[0] * vB.data[1] - vA.data[1] * vB.data[0]);
}

vect3 unit_vector(const vect3 &v)
{
	return v / v.length_squared();
}

using point = vect3;
using color	= vect3;

#endif