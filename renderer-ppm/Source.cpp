// LEARNING SOURCE: https://raytracing.github.io/books/RayTracingInOneWeekend.html

#include "utility.h"

#include "color.h"
#include "sphere.h"
#include "hittable_list.h"

#include <iostream>
#include <fstream>

color ray_color(const Ray& r, const hittable& world){
	hit_record rec;

	if(world.hit(r, 0, infinity, rec)){
		return .5 * (rec.normal + color(1.0, 1.0, 1.0)); // rec normal artifact
	}

	//bg gradient
	vect3 unit_dir = unit_vector(r.direction());
	double t = .5*(unit_dir.y() + 1.0);

	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(.5, .7, 1.0);
}

int main() {
	std:: cout << "-Initialize\n";
	//image specs
	const double aspect_ratio	= 16.0 / 9.0;
	const int image_width 		= 400;
	const int image_height 		= static_cast<int>(image_width / aspect_ratio);

	//world
	hittable_list world;
	world.add(make_shared<sphere>(point(0, 0, -1.0), .5));
	world.add(make_shared<sphere>(point(0, -100.5, -1.0), 100.0));

	//camera
	double viewport_height 	= 2.0;
	double viewport_width 	= aspect_ratio * viewport_height;
	double focal_length 	= 1.0;

	point origin 		= point(0, 0, 0);
	vect3 horizontal 	= vect3(viewport_width, 0, 0);
	vect3 vertical 		= vect3(0, viewport_height, 0);

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
				
				Ray r(origin, lower_left_corner +  horizontal * u + vertical * v);
				color pixel_color = std::move(ray_color(r, world));

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