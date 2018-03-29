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

    create_circle(s, 250.0, {250.0, 250.0}, {0.0, 0.0, 1.0, 1.0});

    for (int i = 0; i < 51; ++i) {
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
