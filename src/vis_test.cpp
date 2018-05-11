#include <iostream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <vector>

#include "../include/camera.h"
#include "../include/scene.h"
#include "../include/shapes.h"
#include "../include/color.h"

int main() {
    camera cam(vec{400, 400});
    scene s = scene({400, 400}, {0, 0, 0, 1});

    auto root = std::make_shared<ellipse>(color{1.0, 0.0, 0.0, 1.0},
                                          vec{200.0, 110.0}, vec{0.0, 0.0},
                                          0.0, true);
    root->add_animator<vec_animator>(0, 49, &root->size, vec{0.0, 0.0},
                                     vec{50.0, 50.0});

    auto line_a = std::make_shared<line>(color{1.0, 1.0, 1.0, 1.0},
                                         vec{200.0, 110.0},
                                         vec{200.0, 110.0});
    line_a->add_animator<vec_animator>(0, 49, &line_a->end, vec{200.0, 110.0},
                                       vec{110.0, 210.0});

    auto line_b = std::make_shared<line>(color{1.0, 1.0, 1.0, 1.0},
                                         vec{200.0, 110.0},
                                         vec{200.0, 110.0});
    line_b->add_animator<vec_animator>(0, 49, &line_b->end, vec{200.0, 110.0},
                                       vec{310.0, 210.0});

    auto a_node = std::make_shared<ellipse>(color{1.0, 0.0, 0.0, 1.0},
                                            vec{110.0, 210.0},
                                            vec{0.0, 0.0}, 0.0, true);
    a_node->add_animator<vec_animator>(0, 49, &a_node->size, vec{0.0, 0.0},
                                       vec{50.0, 50.0});

    auto b_node = std::make_shared<ellipse>(color{1.0, 0.0, 0.0, 1.0},
                                            vec{310.0, 210.0},
                                            vec{0.0, 0.0}, 0.0, true);
    b_node->add_animator<vec_animator>(0, 49, &b_node->size, vec{0.0, 0.0},
                                       vec{50.0, 50.0});

    s.add_layer();
    s.add_shape(line_a, 1);
    s.add_shape(line_b, 1);
    s.add_shape(a_node, 0);
    s.add_shape(b_node, 0);
    s.add_shape(root, 0);

    cam.add_module<video_module>("/tmp/video.mp4", cam.size, 25);

    for (int i = 0; i < 100; ++i) {
        s.update(i);
        cam.encode_frame(s);
    }

    cam.close_modules();

    return 0;
}
