#include "../../include/objects/object.h"

void object::update(const int frame) {
    for (auto& a : animators) {
        a->update(frame);
    }
}
