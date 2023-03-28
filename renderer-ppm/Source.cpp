// LEARNING SOURCE: https://raytracing.github.io/books/RayTracingInOneWeekend.html

#include "utility.h"

#include "camera.h"

#include "color.h"
#include "sphere.h"
#include "hittable_list.h"

#include <iostream>
#include <fstream>

color ray_color(const Ray& r, const hittable& world) {
	hit_record rec;

	if(world.hit(r, 0, infinity, rec)){
		point tgt = rec.p + rec.normal + random_in_unit_sphere();
		return .5 * ray_color(Ray(rec.p, tgt - rec.p), world);
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
	const int samples_per_pixel = 100;

	//world
	hittable_list world;
	world.add(make_shared<sphere>(point(0, 0, -1.0), .5));
	world.add(make_shared<sphere>(point(0, -100.5, -1.0), 100.0));

	//camera
	camera cam;

	//render
	std::cout << "-Attempting to open stream for writing\n";
	std::ofstream ofs;
	ofs.open("../output_2.ppm");

	if(ofs.is_open()){
		std:: cout << "-Stream open for writing\n";

		ofs << "P3\n" << image_width << ' ' << image_height << "\n255\n"; // ppm header

		for (int j = image_height - 1; j >= 0; j--){
			//std::cout << "scanlines remaining: " << i << '\n';

			for (int i = 0; i < image_width; i++){
				color pixel_color(0, 0, 0);

				for(int s = 0; s < samples_per_pixel; s++){
					double u = (i + random_d()) / (image_width - 1.0);
					double v = (j + random_d()) / (image_height - 1.0);

					Ray r = cam.get_ray(u, v);
					pixel_color = std::move(pixel_color + ray_color(r, world));
				}

				write_color(ofs, pixel_color, samples_per_pixel);
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