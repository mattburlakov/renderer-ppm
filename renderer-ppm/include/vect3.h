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
		return std::sqrt(length_squared());
		
	}

	double length_squared() const {
		return pow(data[0], 2) +
			   pow(data[1], 2) +
			   pow(data[2], 2);
	}

	bool near_zero() const {
		const double s = 1e-8;
		return (std::fabs(data[0]) < s) && (std::fabs(data[1]) < s) && (std::fabs(data[2]) < 2);
	}

	inline static vect3 random() {
		return vect3(random_d(), random_d(), random_d());
	}
	inline static vect3 random(double min, double max) {
		return vect3(random_d(min, max), random_d(min, max), random_d(min, max));
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

inline vect3 operator*(vect3 &vA, const vect3 &vB) {
	return vect3(vA.data[0] * vB.data[0],
				 vA.data[1] * vB.data[1],
				 vA.data[2] * vB.data[2]);
}

inline vect3 operator*(const vect3& vA, double k) {
	return vect3(vA.data[0] * k,
				 vA.data[1] * k,
				 vA.data[2] * k);
}
inline vect3 operator*(double k, const vect3 &vA) {
	return vect3(k * vA.data[0],
				 k * vA.data[1],
				 k * vA.data[2]);
}

inline vect3 operator/(const vect3& vA, double k) {
	return vect3 (vA.data[0] / k,
				  vA.data[1] / k,
				  vA.data[2] / k);
}

inline double dot(const vect3 &vA, const vect3 &vB) {
	return (vA.data[0] * vB.data[0] +
			vA.data[1] * vB.data[1] +
			vA.data[2] * vB.data[2]);
}

inline vect3 cross(const vect3 &vA, const vect3 &vB) {
	return vect3(vA.data[1] * vB.data[2] - vA.data[2] * vB.data[1],
				 vA.data[2] * vB.data[0] - vA.data[0] * vB.data[2],
				 vA.data[0] * vB.data[1] - vA.data[1] * vB.data[0]);
}

inline vect3 unit_vector(const vect3 &v) {
	return v / v.length();
}

inline vect3 reflect(const vect3& v, const vect3& n) {
	return v - 2 * dot(v, n) * n;
}

inline vect3 random_in_unit_sphere() {
	while (true)
	{
		vect3 p = std::move(vect3::random(-1.0, 1.0));
		if (p.length_squared() >= 1.0)
			continue;
		return p;
	}
}

inline vect3 random_in_henisphere(const vect3& normal) {
	vect3 in_unit_sphere = random_in_unit_sphere();

	if(dot(in_unit_sphere, normal) > 0) return in_unit_sphere;
	else return -in_unit_sphere;
}

inline vect3 random_unit_vector() {
	return unit_vector(random_in_unit_sphere());
}

inline vect3 refract(const vect3& uv, const vect3& n, double etai_over_etat) {
	double cos_theta = std::fmin(dot(-uv, n), 1.0);

	vect3 r_out_perp 	 = etai_over_etat * (uv + cos_theta * n);
	vect3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;

	return r_out_perp + r_out_parallel;
}

using point = vect3;
using color	= vect3;

#endif