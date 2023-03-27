// LEARNING SOURCE: https://raytracing.github.io/books/RayTracingInOneWeekend.html

#include "vect3.h"
#include "color.h"
#include "Ray.h"

#include <iostream>
#include <fstream>
#include <vector>

double sphere_hit(const point& center, double radius, const Ray& r){
	vect3 sc = std::move(r.origin() - center);

	double a = r.direction().length_squared();
	double b = dot(sc, r.direction());
	double c = sc.length_squared() - radius * radius;

	double discriminant = b * b - a * c;

	if(discriminant < 0) return -1.0;
	else return (-b - std::sqrt(discriminant)) / a;
}

color ray_color(const Ray& r){
	double t = sphere_hit(point(0, 0, -1.0), .5, r);
	if(t > 0.0){
		vect3 normal = unit_vector(r.at(t) - vect3(0, 0, -1.0));
		return .5 * color(normal.x() + 1.0, normal.y() + 1.0, normal.z() + 1.0);
	}

	vect3 unit_dir = unit_vector(r.direction());
	t = .5*(unit_dir.y() + 1.0);

	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(.5, .7, 1.0);
}

int main() {
	std:: cout << "-Initialize\n";
	//image specs
	const double aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	//camera
	double viewport_height = 2.0;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;

	point origin = point(0, 0, 0);
	vect3 horizontal = vect3(viewport_width, 0, 0);
	vect3 vertical = vect3(0, viewport_height, 0);
	vect3 lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - vect3(0, 0, focal_length);

	//render
	std::cout << "-Attempting to open stream for writing\n";
	std::ofstream ofs;
	ofs.open("../output_2.ppm");

	if(ofs.is_open()){
		std:: cout << "-Stream open for writing\n";

		ofs << "P3\n" << image_width << ' ' << image_height << "\n255\n"; // ppm header

		for (int i = image_height - 1; i >= 0; i--)
		{
			//std::cout << "scanlines remaining: " << i << '\n';

			for (int j = 0; j < image_width; j++)
			{
				double u = double(j) / (image_width - 1.0);
				double v = double(i) / (image_height - 1.0);
				
				Ray r(origin, lower_left_corner +  horizontal * u + vertical * v - origin);
				color pixel_color = std::move(ray_color(r));

				write_color(ofs, pixel_color);
			}
		}

		std::cout << "-Writing complete, closing the stream\n";
		ofs.close();
	}
	else{
		std::cout << "Unable to open/create file\n";
	}

	return 0;
}