#include <iostream>
#include <fstream>
#include <vector>

void render() {
	const int width = 256;
	const int height = 256;

	std::ofstream ofs;
	ofs.open("./output.ppm");
	ofs << "P6\n" << width << " " << height << "\n255\n";  //ppm header

	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			double r = double(i) / (width - 1);
			double g = double(j) / (height - 1);
			double b = 0.25;

			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);
			ofs << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}

	ofs.close();
}

int main() {
	render();
	return 0;
}