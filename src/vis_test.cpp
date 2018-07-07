#include <iostream>
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

    std::cout << title.use_count() << std::endl;

    for (int i = 0; i < 200; ++i) {
        world.update(i);
        cam.encode_frame(world);
    }

    world.clear();
}

void second_scene(camera& cam, scene& world) {
    auto title = std::make_shared<text>(vec{0, 600}, 50,
                                        std::string("GathVL Test"));

    world.add_shape(title, 0);

    for (int i = 0; i < 50; ++i) {
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
