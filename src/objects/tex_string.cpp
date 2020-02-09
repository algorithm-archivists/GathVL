#include "../../include/objects/tex_string.h"
#include "../../include/stb_image.h"
#include "../../include/stb_image_resize.h"
#include "../../include/systems/system.h"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <random>
#include <vector>

static const char tex_template[] =
    "\\documentclass[preview]{standalone}\n"
    "\\usepackage{amsmath}\n"
    "\\usepackage{amssymb}\n\n"
    "\\begin{document}\n";

static std::string string_generator() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(97, 122);

    int loop_len = (int)dis(gen) % 10 + 5;
    std::string ret("tex_string_file_");

    for (int i = 0; i < loop_len; ++i) {
        ret.push_back((char)dis(gen));
    }

    ret += "_.";

    return ret;
}

static int tex_to_png(const std::string& str, const std::string& url) {
    std::ofstream tex_file(url + "tex", std::ios_base::out);

    tex_file.write(tex_template, sizeof(tex_template) - 1);
    tex_file.write(str.c_str(), str.size());
    tex_file.write("\n\\end{document}", 15);

    tex_file.close();

    std::vector<std::string> latex_args =
        {"latex", url + "tex"};

    if (subprocess("/usr/bin/latex", latex_args)) {
        return 1;
    }

    std::vector<std::string> png_args = {"dvipng", url + "dvi", "-D", "2000",
        "-bg", "transparent","-o", url + "png"};

    return subprocess("/usr/bin/dvipng", png_args);
}

static inline void format_converter(unsigned char *in, unsigned char *out,
                                    int width, int height) {

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width * 4; j += 4) {
            out[j + 2] = in[j];
            out[j + 1] = in[j + 1];
            out[j] = in[j + 2];
            out[j + 3] = in[j + 3];
        }
        out += width * 4;
        in += width * 4;
    }
}

void tex_string::draw(cairo_t *ctx) const {
    if (image_data) {
        int stride = 0;
        unsigned char *data = nullptr;
        cairo_surface_t *surface;

        if (size.x <= 0 || size.y <= 0 ||
            (size.x == width && size.y == height)) {

            stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, width);
            data = new unsigned char[stride * height];

            if (!data) {
                std::cout << "Malloc failed in tex_string." << std::endl;
                return;
            }

            format_converter(image_data, data, width, height);

            surface =
                cairo_image_surface_create_for_data(data, CAIRO_FORMAT_ARGB32,
                                                    width, height, stride);
        } else {
            stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32,
                                                   (int)size.x);

            data = new unsigned char[stride * (int)size.y];

            if (!data) {
                std::cout << "Malloc for data failed in tex_string."
                    << std::endl;
                return;
            }

            unsigned char *tmp = new unsigned char[(int)(size.x * size.y * 4)];

            if (!tmp) {
                std::cout << "Malloc failed in tex_string." << std::endl;
                delete[] data;
                return;
            }

            stbir_resize_uint8(image_data, width, height, 0,
                               tmp, size.x, size.y, 0, 4);

            format_converter(tmp, data, (int)size.x, (int)size.y);

            surface =
                cairo_image_surface_create_for_data(data, CAIRO_FORMAT_ARGB32,
                                                    (int)size.x, (int)size.y,
                                                    stride);

            delete[] tmp;
        }

        cairo_save(ctx);
        cairo_translate(ctx, location.x, location.y);
        cairo_rotate(ctx, rotation);

        cairo_set_source_rgba(ctx, clr.r, clr.g, clr.b, clr.a);
        cairo_mask_surface(ctx, surface, 0, 0);
        cairo_fill(ctx);

        cairo_restore(ctx);

        cairo_surface_destroy(surface);
        delete[] data;
    }
}

tex_string::tex_string(const std::string& str, vec location, vec size,
                       double rotation, color clr)
    : location(location), size(size), rotation(rotation), clr(clr) {

    texfile = string_generator();

    if (tex_to_png(str, texfile)) {
        std::cout << "Failed to make Latex png file." << std::endl;
        return;
    }

    std::string tmp = texfile + "png";
    image_data = stbi_load(tmp.c_str(), &width, &height, NULL, 4);

    if (!image_data) {
        std::cout << "The image " << tmp << " can't be opened." << std::endl;
    }
}

tex_string::~tex_string() {
    std::string tmp = texfile + "tex";
    if (std::remove(tmp.c_str()) != 0) {
        std::cout << "The file " << tmp << " hasn't been removed" << std::endl;
    }

    tmp = texfile + "dvi";
    if (std::remove(tmp.c_str()) != 0) {
        std::cout << "The file " << tmp << " hasn't been removed" << std::endl;
    }

    tmp = texfile + "log";
    if (std::remove(tmp.c_str()) != 0) {
        std::cout << "The file " << tmp << " hasn't been removed" << std::endl;
    }

    tmp = texfile + "aux";
    if (std::remove(tmp.c_str()) != 0) {
        std::cout << "The file " << tmp << " hasn't been removed" << std::endl;
    }

    tmp = texfile + "png";
    if (std::remove(tmp.c_str()) != 0) {
        std::cout << "The file " << tmp << " hasn't been removed" << std::endl;
    }

    stbi_image_free(image_data);
}
