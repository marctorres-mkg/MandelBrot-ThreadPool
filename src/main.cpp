#include <iostream>
#include <vector>

#include "mandelbrot.h"

using namespace std;

int main(void) {
    const int width = 800;
    const int height = 800;
    const int max_iter = 1000;

    vector<unsigned char> pixels(width * height * 3);

    long long duration = measure_time([&]() { mandelbrot(pixels, width, height, max_iter); });
    cout << "Time taken (with threading): " << duration << " ms" << endl;

    writePPM("images/mandelbrot.ppm", width, height, pixels);

    long long duration_no_tp = measure_time([&]() { mandelbrot_no_tp(pixels, width, height, max_iter); });
    cout << "Time taken (without threading): " << duration_no_tp << " ms" << endl;

    return 0;
}