#include "../include/png_encoder.h"

#include <sstream>
#include <iomanip>

void png_encoder::encode(cairo_surface_t *image) {
    std::string png_url;
    std::stringstream ss;
    ss << std::setw(5) << std::setfill('0') << count;
    png_url = url + ss.str() + ".png";
    cairo_surface_write_to_png(image, png_url.c_str());
    count++;
}

png_encoder::png_encoder(std::string url) : encoder(url), count(0) {}
