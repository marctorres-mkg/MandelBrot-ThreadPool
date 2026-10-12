#include <vector>
#include <string>
#include <chrono>

template <typename Func>
long long measure_time(Func f) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return duration.count();
}

void writePPM(const std::string& filename, int width, int height, const std::vector<unsigned char>& pixels);
void hsv_to_rgb(double h, double s, double v, unsigned char& r, unsigned char& g, unsigned char& b);

void compute_pixel(int x, int y, int width, int height, int max_iter, std::vector<unsigned char>& pixels);
void mandelbrot(std::vector<unsigned char>& pixels, int width, int height, int max_iter);
void mandelbrot_no_tp(std::vector<unsigned char>& pixels, int width, int height, int max_iter);