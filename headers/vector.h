#ifndef VECTOR_H
#define VECTOR_H
#pragma once

#include <cmath>
#include <iostream>

using std::sqrt;

class vector {
    public:
        vector() : e{0,0,0} {}
        vector(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vector operator-() const { return vector(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        vector& operator+=(const vector &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vector& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vector& operator/=(const double t) {
            return *this *= 1/t;
        }

        double length() const {
            return sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

    public:
        double e[3];
};

// Type aliases for vector
using point3 = vector;   // 3D point
using color = vector;    // RGB color

#endif

// vector Utility Functions

inline std::ostream& operator<<(std::ostream &out, const vector &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vector operator+(const vector &u, const vector &v) {
    return vector(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vector operator-(const vector &u, const vector &v) {
    return vector(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vector operator*(const vector &u, const vector &v) {
    return vector(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vector operator*(double t, const vector &v) {
    return vector(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vector operator*(const vector &v, double t) {
    return t * v;
}

inline vector operator/(vector v, double t) {
    return (1/t) * v;
}

inline double dot(const vector &u, const vector &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vector cross(const vector &u, const vector &v) {
    return vector(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vector unit_vector(vector v) {
    return v / v.length();
}

inline bool operator!=(const vector& u, const vector& v) {
    return u.e[0] != v.e[0] || u.e[1] != v.e[1] || u.e[2] != v.e[2];
}

inline bool operator==(const vector& u, const vector& v) {
    return u.e[0] == v.e[0] || u.e[1] == v.e[1] || u.e[2] == v.e[2];
}