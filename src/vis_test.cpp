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
    s.layers[1].shapes.emplace_back(line_a);
    s.layers[1].shapes.emplace_back(line_b);
    s.layers[0].shapes.emplace_back(a_node);
    s.layers[0].shapes.emplace_back(b_node);
    s.layers[0].shapes.emplace_back(root);

    vec_multianimator ma = vec_multianimator();
    ma.params.push_back({&root->size, {0.0, 0.0}, {50.0, 50.0}, 0, 49});
    ma.params.push_back({&a_node->size, {0.0, 0.0}, {50.0, 50.0}, 0, 49});
    ma.params.push_back({&b_node->size, {0.0, 0.0}, {50.0, 50.0}, 0, 49});
    ma.params.push_back({&line_a->end, {200.0, 110.0}, {110.0, 210.0}, 0, 49});
    ma.params.push_back({&line_b->end, {200.0, 110.0}, {310.0, 210.0}, 0, 49});

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
