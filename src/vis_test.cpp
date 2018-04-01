#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "../include/camera.h"
#include "../include/scene.h"
#include "../include/shapes.h"
#include "../include/color.h"
#include "../include/animators.h"

int main() {
    camera cam = camera({400, 400}, "/tmp/img");
    scene s = scene({400, 400}, {0, 0, 0, 1});

    shape root_node = ellipse({1.0, 0.0, 0.0, 1.0}, {200.0, 110.0}, {0.0, 0.0},
                            0.0);

    shape line_a = line({1.0, 1.0, 1.0, 1.0}, {200.0, 110.0}, {110.0, 210.0});
    shape line_b = line({1.0, 1.0, 1.0, 1.0}, {200.0, 110.0}, {310.0, 210.0});

    shape a_node = ellipse({1.0, 0.0, 0.0, 1.0}, {110.0, 210.0}, {0.0, 0.0},
                            0.0);
    shape b_node = ellipse({1.0, 0.0, 0.0, 1.0}, {310.0, 210.0}, {0.0, 0.0},
                            0.0);

    s.shape_vector.push_back(&line_a);
    s.shape_vector.push_back(&line_b);
    s.shape_vector.push_back(&a_node);
    s.shape_vector.push_back(&b_node);
    s.shape_vector.push_back(&root_node);

    vec_animator root_va = vec_animator(0, 49, &root_node.size, {0.0, 0.0},
                                            {50.0, 50.0});
    vec_animator a_va = vec_animator(0, 49, &a_node.size, {0.0, 0.0},
                                        {50.0, 50.0});
    vec_animator b_va = vec_animator(0, 49, &b_node.size, {0.0, 0.0},
                                        {50.0, 50.0});
    vec_animator la_va = vec_animator(0, 49, &line_a.ex.a, {200.0, 110.0},
                                        {110.0, 210.0});
    vec_animator lb_va = vec_animator(0, 49, &line_b.ex.a, {200.0, 110.0},
                                        {310.0, 210.0});

    for (int i = 0; i < 50; ++i) {
        std::string url, number;
        std::stringstream ss;
        ss << std::setw(5) << std::setfill('0') << i;
        number = ss.str();

        root_va.update(i, root_va);
        a_va.update(i, a_va);
        b_va.update(i, b_va);
        la_va.update(i, la_va);
        lb_va.update(i, lb_va);

        url = cam.url_base + number + ".png";
        cam.write_to_png(s, url.c_str());
    }

    return 0;
}
