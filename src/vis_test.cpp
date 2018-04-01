#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "../include/camera.h"
#include "../include/scene.h"
#include "../include/shapes.h"
#include "../include/color.h"
#include "../include/multianimators.h"

int main() {
    camera cam = camera({400, 400}, "/tmp/img");
    scene s = scene({400, 400}, {0, 0, 0, 1});

    shape root_node = ellipse({1.0, 0.0, 0.0, 1.0}, {200.0, 110.0}, {0.0, 0.0},
                            0.0);

    shape line_a = line({1.0, 1.0, 1.0, 1.0}, {200.0, 110.0}, {200.0, 110.0});
    shape line_b = line({1.0, 1.0, 1.0, 1.0}, {200.0, 110.0}, {200.0, 110.0});

    shape a_node = ellipse({1.0, 0.0, 0.0, 1.0}, {110.0, 210.0}, {0.0, 0.0},
                            0.0);
    shape b_node = ellipse({1.0, 0.0, 0.0, 1.0}, {310.0, 210.0}, {0.0, 0.0},
                            0.0);

    s.shape_vector.push_back(&line_a);
    s.shape_vector.push_back(&line_b);
    s.shape_vector.push_back(&a_node);
    s.shape_vector.push_back(&b_node);
    s.shape_vector.push_back(&root_node);

    std::vector<vec_param> param_vec;
    param_vec.push_back({&root_node.size, {0.0, 0.0}, {50.0, 50.0}, 0, 49});
    param_vec.push_back({&a_node.size, {0.0, 0.0}, {50.0, 50.0}, 0, 49});
    param_vec.push_back({&b_node.size, {0.0, 0.0}, {50.0, 50.0}, 0, 49});
    param_vec.push_back({&line_a.ex.a, {200.0, 110.0}, {110.0, 210.0}, 0, 49});
    param_vec.push_back({&line_b.ex.a, {200.0, 110.0}, {310.0, 210.0}, 0, 49});

    vec_multianimator ma = vec_multianimator(param_vec);

    for (int i = 0; i < 50; ++i) {
        std::string url, number;
        std::stringstream ss;
        ss << std::setw(5) << std::setfill('0') << i;
        number = ss.str();

        ma.update(i, ma);

        url = cam.url_base + number + ".png";
        cam.write_to_png(s, url.c_str());
    }

    return 0;
}
