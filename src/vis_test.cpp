#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "../include/camera.h"
#include "../include/scene.h"
#include "../include/shapes.h"
#include "../include/color.h"
#include "../include/animations.h"

int main() {
    camera cam = camera("/tmp/img");
    scene s = scene({600, 400}, {0, 0, 0, 1});

    shape shp;

    std::vector<shape> elp_vec =
        create_ellipse({1.0, 0.0, 0.0, 1.0}, {200.0, 200.0}, {200.0, 200.0},
                            0.0, 50);

    s.shape_vector.push_back(shp);

    for (int i = 0; i < 50; ++i) {
        std::string url, number;
        std::stringstream ss;
        ss << std::setw(5) << std::setfill('0') << i;
        number = ss.str();

        s.shape_vector[0] = elp_vec[i];

        url = cam.url_base + number + ".png";
        cam.write_to_png(s, url.c_str());
    }

    return 0;
}
