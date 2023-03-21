#include "vect3.h"
#include "color.h"
#include "Ray.h"

#include <iostream>
#include <fstream>
#include <vector>

color ray_color(const Ray& r){
	vect3 unit_dir = unit_vector(r.direction());
	double t = .5*(unit_dir.y() + 1.0);
	return color(1.0, 1.0, 1.0) * (1.0 - t) + color(.5, .7, 1.0) * t;
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
	vect3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vect3(0, 0, focal_length);

	//render
	std::cout << "-Attempting to open stream for writing\n";
	std::ofstream ofs;
	ofs.open("../output_2.ppm");

	if(ofs.is_open()){
		std:: cout << "-Stream open for writing\n";

		ofs << "P3\n" << image_width << ' ' << image_height << "\n255\n"; // ppm header

		for (int i = image_height - 1; i >= 0; i--)
		{
			std::cout << "scanlines remaining: " << i << '\n';

			for (int j = 0; j < image_width; j++)
			{
				double u = double(i) / (image_width - 1);
				double v = double(j) / (image_height - 1);
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