#include <iostream>
<<<<<<< HEAD
#include <cmath>
=======
#include <sstream>
#include <iomanip>
#include <math.h>
>>>>>>> ff70994f4868c1058ec63b70f32cdedbaaf85bde
#include <memory>
#include <string>
#include <vector>

#include "../include/camera.h"
#include "../include/scene.h"

<<<<<<< HEAD
void first_scene(camera& cam, scene& world) {
    auto title = std::make_shared<text>(vec{0, 100}, 50,
                                        std::string("GathVL Test"));

    auto ball = std::make_shared<ellipse>(vec{640, 360}, vec{0, 0}, 0, true);

    ball->add_animator<vec_animator>(0, 49, &ball->size, vec{0, 0},
                                     vec{50,50});

    ball->add_animator<vec_animator>(50, 99, &ball->location, vec{640, 360},
                                     vec{-50, -50});

    auto rec = std::make_shared<rectangle>(vec{-50, -50}, vec{50, 50}, 0,
                                           true);

    rec->add_animator<vec_animator>(100, 149, &rec->location, vec{-50, -50},
                                    vec{640, 360});

    rec->add_animator<vec_animator>(150, 199, &rec->size, vec{50, 50},
                                    vec{0, 0});

    world.add_layer();
    world.add_shape(title, 0);
    world.add_shape(ball, 1);
    world.add_shape(rec, 1);

    for (int i = 0; i < 200; ++i) {
        world.update(i);
        cam.encode_frame(world);
    }

    world.clear();
}

void second_scene(camera& cam, scene& world) {
    auto title = std::make_shared<text>(vec{0, 720}, 50,
                                        std::string("GathVL Test"));

    auto y_axis = std::make_shared<line>(vec{50, 10}, vec{50, 610});
    auto x_axis = std::make_shared<line>(vec{1250, 610}, vec{50, 610});

    std::vector<vec> exp_points;

    vec origin = {50, 610};
=======
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

    auto text1 = std::make_shared<text>(vec{20, 300}, 50.0, "GathVL Test");

    auto rec = std::make_shared<rectangle>(vec{200, 200}, vec{10, 10},
                                           M_PI / 4, true);

    auto vector1 = std::make_shared<arrow>(vec{250, 250}, 100, M_PI / 2);

    std::vector<vec> points;

    vec origin = {300, 400};

    for (int i = 0; i < 50; ++i) {
        points.emplace_back(origin.x + i,
                            origin.y - (i * i) / 50);
    }

    auto curve1 = std::make_shared<curve>(points);

    std::vector<vec> hex;
    hex.emplace_back(0, 25);
    hex.emplace_back(12.5, 46.7);
    hex.emplace_back(37.5, 46.7);
    hex.emplace_back(50, 25);
    hex.emplace_back(37.5, 3.4);
    hex.emplace_back(12.5, 3.4);

    auto poly = std::make_shared<polygon>(hex, false);

    s.add_layer();
    s.add_shape(line_a, 1);
    s.add_shape(line_b, 1);
    s.add_shape(a_node, 0);
    s.add_shape(b_node, 0);
    s.add_shape(root, 0);
    s.add_shape(text1, 0);
    s.add_shape(rec, 0);
    s.add_shape(vector1, 0);
    s.add_shape(curve1, 0);
    s.add_shape(poly, 0);

    cam.add_encoder<video_encoder>("/tmp/video.mp4", cam.size, 25);
>>>>>>> ff70994f4868c1058ec63b70f32cdedbaaf85bde

    for (int i = 0; i < 100; ++i) {
        exp_points.emplace_back(origin.x + i * 12,
                                origin.y - 10 - std::exp(i * 0.06) / 0.68);
    }

    auto exp_curve =
        std::make_shared<curve>(std::vector<vec>());

    exp_curve->add_animator<vector_animator<vec>>(0, 50, 0, exp_points,
                                                  &exp_curve->points);

    world.add_shape(title, 0);
    world.add_shape(y_axis, 0);
    world.add_shape(x_axis, 0);
    world.add_shape(exp_curve, 0);

    for (int i = 0; i < 51; ++i) {
        world.update(i);
        cam.encode_frame(world);
    }
}

int main() {
    camera cam(vec{1280, 720});
    scene world = scene({1280, 720}, {0, 0, 0, 1});

    cam.add_encoder<video_encoder>("/tmp/video.mp4", cam.size, 50);

    first_scene(cam, world);

    second_scene(cam, world);

    cam.clear_encoders();

    return 0;
}
