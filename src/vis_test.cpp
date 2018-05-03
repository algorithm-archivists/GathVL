#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "../include/camera.h"
#include "../include/scene.h"
#include "../include/shapes.h"
#include "../include/color.h"

int main() {
    camera cam = camera({400, 400}, "/tmp/img");
    scene s = scene({400, 400}, {0, 0, 0, 1});

    ellipse *root = new ellipse({1.0, 0.0, 0.0, 1.0}, {200.0, 110.0},
                                    {0.0, 0.0}, 0.0, true);

    line *line_a = new line({1.0, 1.0, 1.0, 1.0}, {200.0, 110.0},
                                {200.0, 110.0});
    line *line_b = new line({1.0, 1.0, 1.0, 1.0}, {200.0, 110.0},
                                {200.0, 110.0});

    ellipse *a_node = new ellipse({1.0, 0.0, 0.0, 1.0}, {110.0, 210.0},
                                    {0.0, 0.0}, 0.0, true);
    ellipse *b_node = new ellipse({1.0, 0.0, 0.0, 1.0}, {310.0, 210.0},
                                    {0.0, 0.0}, 0.0, true);

    s.add_layer();
    int line_a_pos = s.add_shape(line_a, 1);
    int line_b_pos = s.add_shape(line_b, 1);
    int a_node_pos = s.add_shape(a_node, 0);
    int b_node_pos = s.add_shape(b_node, 0);
    int root_pos = s.add_shape(root, 0);

    s.add_animator(new vec_animator(0, 49, &root->size, {0.0, 0.0},
                                        {50.0, 50.0}), 0, root_pos);
    s.add_animator(new vec_animator(0, 49, &a_node->size, {0.0, 0.0},
                                        {50.0, 50.0}), 0, a_node_pos);
    s.add_animator(new vec_animator(0, 49, &b_node->size, {0.0, 0.0},
                                        {50.0, 50.0}), 0, b_node_pos);
    s.add_animator(new vec_animator(0, 49, &line_a->end, {200.0, 110.0},
                                        {110.0, 210.0}), 1, line_a_pos);
    s.add_animator(new vec_animator(0, 49, &line_b->end, {200.0, 110.0},
                                        {310.0, 210.0}), 1, line_b_pos);

    for (int i = 0; i < 50; ++i) {
        std::string url, number;
        std::stringstream ss;
        ss << std::setw(5) << std::setfill('0') << i;
        number = ss.str();

        s.update(i);

        url = cam.url_base + number + ".png";
        cam.write_to_png(s, url.c_str());
    }

    return 0;
}
