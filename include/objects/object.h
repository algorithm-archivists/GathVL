#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <vector>

#include <cairo.h>

#include "../animators/vec_animator.h"
#include "../animators/vector_animator.h"

struct object {
    std::vector<std::unique_ptr<animator>> animators;

    template <typename A, typename... Args>
    void add_animator(Args&&... args) {
        using namespace std;
        animators.emplace_back(make_unique<A>(forward<Args>(args)...));
    }

    virtual void draw(cairo_t *) const = 0;
    void update(const int frame);

    virtual ~object() {}
};

#endif //OBJECT_H
