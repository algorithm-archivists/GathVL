#ifndef ANIMATOR_H
#define ANIMATOR_H

struct animator {
    int start_frame, end_frame;

    virtual void update(const int frame) = 0;

    animator(int start, int end) : start_frame(start), end_frame(end) {}
    virtual ~animator() {}
};

#endif //ANIMATOR_H
