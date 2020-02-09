#include "../../include/objects/image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../include/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../../include/stb_image_resize.h"

#include <cstdlib>
#include <iostream>

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

void image::draw(cairo_t *ctx) const {
    if (image_data) {
        int stride = 0;
        unsigned char *data = nullptr;
        cairo_surface_t *surface;

        if (size.x <= 0 || size.y <= 0 ||
            (size.x == width && size.y == height)) {

            stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, width);
            data = new unsigned char[stride * height];

            if (!data) {
                std::cout << "Malloc for data failed in image." << std::endl;
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
                std::cout << "Malloc for data failed in image." << std::endl;
                return;
            }

            unsigned char *tmp = new unsigned char[(int)(size.x * size.y * 4)];

            if (!tmp) {
                std::cout << "Malloc failed in image." << std::endl;
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

        cairo_set_source_surface(ctx, surface, 0, 0);

        if (size.x <= 0 || size.y <= 0 ||
            (size.x == width && size.y == height)) {
            cairo_rectangle(ctx, 0, 0, width, height);
        } else {
            cairo_rectangle(ctx, 0, 0, size.x, size.y);
        }

        cairo_clip(ctx);
        cairo_paint(ctx);

        cairo_restore(ctx);

        cairo_surface_destroy(surface);
        delete[] data;
    }
}

image::image(const std::string& url, vec location, double rotation, vec size)
    : location(location), rotation(rotation), size(size) {

    image_data = stbi_load(url.c_str(), &width, &height, NULL, 4);

    if (!image_data) {
        std::cout << "The image " << url << "can't be opened." << std::endl;
    }
}

image::~image() {
    stbi_image_free(image_data);
}
