#include <iostream>
#include <sstream>
#include <iomanip>
#include "../include/camera.h"
#include "../include/scene.h"
#include "../include/shapes.h"
#include "../include/color.h"

int main() {
    camera cam = camera({250, 250}, {500, 500});
    scene s = scene({1000, 1000}, "/tmp/img");

    shape elps = ellipse({1.0, 0.0, 0.0, 1.0}, {500.0, 500.0}, {200.0, 200.0},
                            0.0);

    s.shape_vector.push_back(elps);

    s.draw();

    for (int i = 0; i < 50; ++i) {
        std::string url, number;
        std::stringstream ss;
        ss << std::setw(5) << std::setfill('0') << i;
        number = ss.str();

        cam.move({-5, -5});

        url = s.url_base + number + ".png";
        cam.write_to_png(s, url.c_str());
    }

    return 0;
}
