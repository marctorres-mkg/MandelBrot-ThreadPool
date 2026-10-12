#include <iostream>
#include <cmath>
#include <complex>
#include <fstream>

#include "threadpool.h"

using namespace std;

void writePPM(const std::string& filename, int width, int height, const std::vector<unsigned char>& pixels) {
    std::ofstream ofs(filename, std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    ofs.write(reinterpret_cast<const char*>(pixels.data()), pixels.size());
    ofs.close();
}

void hsv_to_rgb(double h, double s, double v, unsigned char& r, unsigned char& g, unsigned char& b) {
    double c = v * s;
    double x = c * (1 - abs(fmod(h / 60.0, 2) - 1));
    double m = v - c;

    double r_prime, g_prime, b_prime;
    if (h >= 0 && h < 60) { r_prime = c; g_prime = x; b_prime = 0; }
    else if (h >= 60 && h < 120) { r_prime = x; g_prime = c; b_prime = 0; }
    else if (h >= 120 && h < 180) { r_prime = 0; g_prime = c; b_prime = x; }
    else if (h >= 180 && h < 240) { r_prime = 0; g_prime = x; b_prime = c; }
    else if (h >= 240 && h < 300) { r_prime = x; g_prime = 0; b_prime = c; }
    else { r_prime = c; g_prime = 0; b_prime = x; }

    r = (unsigned char)((r_prime + m) * 255.0);
    g = (unsigned char)((g_prime + m) * 255.0);
    b = (unsigned char)((b_prime + m) * 255.0);
}

mutex print_mtx;

int main(void) {
    const int width = 800;
    const int height = 800;
    const int max_iter = 2000;

    std::vector<unsigned char> pixels(width * height * 3);

    {
        ThreadPool pool(thread::hardware_concurrency());
    
        for (int y = 0; y < height; y++) {
            pool.add_task([y, width, height, max_iter, &pixels]() {
                for (int x = 0; x < width; x++) {
                    complex<double> c((double)x / width * 3 - 2.2, (double)y / height * 3 - 1.5);
                    complex<double> z(0);

                    int iter = 0;
                    while (abs(z) < 4.0 && iter < max_iter) {
                        z = z * z + c;
                        iter++;
                    }
                    
                    unsigned char r = 0, g = 0, b = 0;

                    if (iter < max_iter) {
                        double nu = log(log(norm(z))) / log(2.0);
                        double cont_iter = iter + 1 - nu;

                        double hue = fmod(cont_iter * 5, 360.0); 
                        
                        hsv_to_rgb(hue, 1.0, 1.0, r, g, b);
                    }
                    pixels[(y * width + x) * 3 + 0] = r; 
                    pixels[(y * width + x) * 3 + 1] = g; 
                    pixels[(y * width + x) * 3 + 2] = b;
                }
            });
        }
    }

    writePPM("mandelbrot.ppm", width, height, pixels);

    return 0;
}