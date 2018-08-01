#include "../../include/objects/image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../include/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../../include/stb_image_resize.h"

#include <cstdlib>

void image::draw(cairo_t *ctx) const {
    if (surface) {
        cairo_save(ctx);
        cairo_translate(ctx, location.x, location.y);
        cairo_rotate(ctx, rotation);

        cairo_set_source_surface(ctx, surface, 0, 0);
        cairo_rectangle(ctx, 0, 0, size.x, size.y);
        cairo_clip(ctx);
        cairo_paint(ctx);

        cairo_restore(ctx);
    }
}

image::image(const std::string& url, vec location, double rotation,
             vec image_size)
    : location(location + vec{700,0}), rotation(rotation), size(image_size) {

    int width, height;
    unsigned char *data = stbi_load(url.c_str(), &width, &height, NULL, 4);

    if (!data) {
        surface = nullptr;
        return;
    }

    int stride = 0;

    if (size.x <= 0 || size.y <= 0 || (size.x == width && size.y == height)) {
        size.x = width;
        size.y = height;

        stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, size.x);

        image_data = new unsigned char[stride * height];

        if (!image_data) {
            surface = nullptr;
            stbi_image_free(data);
            return;
        }

        unsigned char *out_row = image_data;
        unsigned char *in_row = data;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width * 4; j += 4) {
                    out_row[j + 2] = in_row[j];
                    out_row[j + 1] = in_row[j + 1];
                    out_row[j] = in_row[j + 2];
                    out_row[j + 3] = in_row[j + 3];
            }
            out_row += width * 4;
            in_row += width * 4;
        }
    } else {
        stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, size.x);
        unsigned char tmp[(int)(size.x * size.y * 4)];
        image_data = new unsigned char[stride * (int)size.y];

        if (!image_data) {
            surface = nullptr;
            stbi_image_free(data);
            return;
        }

        stbir_resize_uint8(data, width, height, 0, tmp, size.x, size.y, 0, 4);

        unsigned char *out_row = image_data;
        unsigned char *in_row = tmp;
        for (int i = 0; i < size.y; ++i) {
            for (int j = 0; j < size.x * 4; j += 4) {
                    out_row[j + 2] = in_row[j];
                    out_row[j + 1] = in_row[j + 1];
                    out_row[j] = in_row[j + 2];
                    out_row[j + 3] = in_row[j + 3];
            }
            out_row += (int)size.x * 4;
            in_row += (int)size.x * 4;
        }
    }

    surface =
        cairo_image_surface_create_for_data(image_data, CAIRO_FORMAT_ARGB32,
                                            (int)size.x, (int)size.y, stride);

    stbi_image_free(data);
}

image::~image() {
    cairo_surface_destroy(surface);
    delete[] image_data;
}
