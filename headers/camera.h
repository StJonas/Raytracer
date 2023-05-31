#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

class camera {
public:
    // Constructors
    camera(){};
    camera(const vec3& position, const vec3& lookAt, const vec3& up, double horizontalFOV,
               int resolutionHorizontal, int resolutionVertical, int maxBounces)
    : position(position),
      lookAt(lookAt),
      up(up),
      horizontalFOV(horizontalFOV),
      resolutionHorizontal(resolutionHorizontal),
      resolutionVertical(resolutionVertical),
      maxBounces(maxBounces) {}

    // Getter methods
    vec3 getPosition() const;
    vec3 getLookAt() const;
    vec3 getUp() const;
    double getHorizontalFOV() const;
    int getResolutionHorizontal() const;
    int getResolutionVertical() const;
    int getMaxBounces() const;

    // Setter methods
    void setPosition(const vec3& position);
    void setLookAt(const vec3& lookAt);
    void setUp(const vec3& up);
    void setHorizontalFOV(double horizontalFOV);
    void setResolutionHorizontal(int resolutionHorizontal);
    void setResolutionVertical(int resolutionVertical);
    void setMaxBounces(int maxBounces);

private:
    vec3 position;
    vec3 lookAt;
    vec3 up;
    double horizontalFOV;
    int resolutionHorizontal;
    int resolutionVertical;
    int maxBounces;
};


// Getter methods
vec3 camera::getPosition() const {
    return position;
}

vec3 camera::getLookAt() const {
    return lookAt;
}

vec3 camera::getUp() const {
    return up;
}

double camera::getHorizontalFOV() const {
    return horizontalFOV;
}

int camera::getResolutionHorizontal() const {
    return resolutionHorizontal;
}

int camera::getResolutionVertical() const {
    return resolutionVertical;
}

int camera::getMaxBounces() const {
    return maxBounces;
}

// Setter methods
void camera::setPosition(const vec3& position) {
    this->position = position;
}

void camera::setLookAt(const vec3& lookAt) {
    this->lookAt = lookAt;
}

void camera::setUp(const vec3& up) {
    this->up = up;
}

void camera::setHorizontalFOV(double horizontalFOV) {
    this->horizontalFOV = horizontalFOV;
}

void camera::setResolutionHorizontal(int resolutionHorizontal) {
    this->resolutionHorizontal = resolutionHorizontal;
}

void camera::setResolutionVertical(int resolutionVertical) {
    this->resolutionVertical = resolutionVertical;
}

void camera::setMaxBounces(int maxBounces) {
    this->maxBounces = maxBounces;
}

#endif