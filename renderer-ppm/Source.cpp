#include "vect3.h"
#include "color.h"

#include <iostream>
#include <fstream>
#include <vector>

void render() {
	const int width = 256;
	const int height = 256;

	std::ofstream ofs;
	ofs.open("./output.ppm");
	ofs << "P3\n" << width << ' ' << height << "\n255\n";  //ppm header

	for (int i = height - 1; i >= 0; i--) {
		std::system("cls");
		std::cout << "scanlines remaining: " << i << '\n';

		for (int j = 0; j < width; j++) {
			color pixel_color(double(i) / (width - 1), double(j) / (height - 1), 0.25);
			write_color(ofs, pixel_color);
		}
	}

	std::cout << "done" << '\n';

	ofs.close();
}

int main() {
	render();
	return 0;
}