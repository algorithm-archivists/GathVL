#include "../include/png_module.h"

#include <sstream>
#include <iomanip>

void png_module::encode(cairo_surface_t *image) {
    std::string png_url;
    std::stringstream ss;
    ss << std::setw(5) << std::setfill('0') << count;
    png_url = url + ss.str() + ".png";
    cairo_surface_write_to_png(image, url.c_str());
    count++;
}

png_module::png_module(std::string url) : camera_module(url), count(0) {}
