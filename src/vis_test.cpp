#include <iostream>
#include <cmath>
#include <memory>
#include <vector>

#include "../include/camera.h"
#include "../include/scene.h"

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
