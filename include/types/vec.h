#ifndef GATHVL_VEC_H
#define GATHVL_VEC_H

#include <cmath>
#include <cstdio>

struct vec {
    double x, y;

    vec() : x(0.0), y(0.0) {}
    vec(double x0) : x(x0), y(0.0) {}
    vec(double x0, double y0) : x(x0), y(y0) {}

    vec& operator+=(vec rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    vec& operator-=(vec rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    vec& operator*=(double rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    vec& operator/=(double rhs) {
        auto inv = 1.0 / rhs;
        x *= inv;
        y *= inv;
        return *this;
    }
};

inline vec operator-(vec lhs) {
    return vec(-lhs.x, -lhs.y);
}

inline vec operator+(vec lhs, vec rhs) {
    return vec(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline vec operator-(vec lhs, vec rhs) {
    return vec(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline vec operator*(vec lhs, double b) {
    return vec(lhs.x * b, lhs.y * b);
}

inline vec operator*(double lhs, vec rhs) {
    return vec(lhs * rhs.x, lhs * rhs.y);
}

inline vec operator/(vec lhs, double rhs) {
    auto inv = 1.0 / rhs;
    return lhs * inv;
}

inline double dot(vec lhs, vec rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

inline double length(vec lhs) {
    return sqrt(dot(lhs, lhs));
}

inline vec normalize(vec lhs) {
    return lhs / length(lhs);
}

inline double distance(vec lhs, vec rhs) {
    return length(lhs - rhs);
}

inline void print(vec v) {
    printf("% .3lf, % .3lf\n", v.x, v.y);
}

#endif //GATHVL_VEC_H
