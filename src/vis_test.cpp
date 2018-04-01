#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <unistd.h>
#include "../include/camera.h"
#include "../include/scene.h"
#include "../include/shapes.h"
#include "../include/color.h"
#include "../include/animations.h"

int main() {
    camera cam = camera("/tmp/img");
    scene s = scene({600, 400}, {0, 0, 0, 1});

    shape shp = ellipse({0.0, 0.0, 1.0, 1.0}, {200.0, 200.0}, {100.0, 100.0},
                            0.0);
    s.shape_vector.push_back(shp);

    vec_animator va = vec_animator(0, 49, &shp.size, {0.0, 0.0}, shp.size);

    for (int i = 0; i < 50; ++i) {
        std::string url, number;
        std::stringstream ss;
        ss << std::setw(5) << std::setfill('0') << i;
        number = ss.str();

        va.update(i);

        url = cam.url_base + number + ".png";
        cam.write_to_png(s, url.c_str());
    }

    return 0;
}
