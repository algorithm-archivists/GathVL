#ifndef GATHVL_COLOR_H
#define GATHVL_COLOR_H

struct color {
    double r, g, b, a;

    color() : r(0.0), g(0.0), b(0.0), a(1.0) {}
    color(double r0, double g0, double b0) : r(r0), g(g0), b(b0), a(1.0) {}
    color(double r0, double g0, double b0, double a0) :
        r(r0), g(g0), b(b0), a(a0) {}

    color& operator+=(color rhs) {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
        a += rhs.a;
        return *this;
    }

    color& operator-=(color rhs) {
        r -= rhs.r;
        g -= rhs.g;
        b -= rhs.b;
        a -= rhs.a;
        return *this;
    }

    color& operator/=(double rhs) {
        auto inv = 1.0 / rhs;
        r *= inv;
        g *= inv;
        b *= inv;
        a *= inv;
        return *this;
    }
};


inline color operator+(color lhs, color rhs) {
    return color(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b, lhs.a + rhs.a);
}

inline color operator-(color lhs, color rhs) {
    return color(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b, lhs.a - rhs.a);
}

inline color operator*(color lhs, double b) {
    return color(lhs.r * b, lhs.g * b, lhs.b * b, lhs.a * b);
}

inline color operator*(double lhs, color rhs) {
    return color(lhs * rhs.r, lhs * rhs.g, lhs * rhs.b, lhs * rhs.a);
}

inline color operator/(color lhs, double rhs) {
    auto inv = 1.0 / rhs;
    return lhs * inv;
}

#endif //GATHVL_COLOR_H
