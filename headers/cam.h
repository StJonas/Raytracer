#ifndef CAM_H
#define CAM_H

#include "vector.h"

class cam {
public:
    // Constructors
    cam(){};
    cam(const vector& position, const vector& lookAt, const vector& up, double horizontalFOV,
               int resolutionHorizontal, int resolutionVertical, int maxBounces)
    : position(position),
      lookAt(lookAt),
      up(up),
      horizontalFOV(horizontalFOV),
      resolutionHorizontal(resolutionHorizontal),
      resolutionVertical(resolutionVertical),
      maxBounces(maxBounces) {}

    // Getter methods
    vector getPosition() const;
    vector getLookAt() const;
    vector getUp() const;
    double getHorizontalFOV() const;
    int getResolutionHorizontal() const;
    int getResolutionVertical() const;
    int getMaxBounces() const;

    // Setter methods
    void setPosition(const vector& position);
    void setLookAt(const vector& lookAt);
    void setUp(const vector& up);
    void setHorizontalFOV(double horizontalFOV);
    void setResolutionHorizontal(int resolutionHorizontal);
    void setResolutionVertical(int resolutionVertical);
    void setMaxBounces(int maxBounces);

private:
    vector position;
    vector lookAt;
    vector up;
    double horizontalFOV;
    int resolutionHorizontal;
    int resolutionVertical;
    int maxBounces;
};


// Getter methods
vector cam::getPosition() const {
    return position;
}

vector cam::getLookAt() const {
    return lookAt;
}

vector cam::getUp() const {
    return up;
}

double cam::getHorizontalFOV() const {
    return horizontalFOV;
}

int cam::getResolutionHorizontal() const {
    return resolutionHorizontal;
}

int cam::getResolutionVertical() const {
    return resolutionVertical;
}

int cam::getMaxBounces() const {
    return maxBounces;
}

// Setter methods
void cam::setPosition(const vector& position) {
    this->position = position;
}

void cam::setLookAt(const vector& lookAt) {
    this->lookAt = lookAt;
}

void cam::setUp(const vector& up) {
    this->up = up;
}

void cam::setHorizontalFOV(double horizontalFOV) {
    this->horizontalFOV = horizontalFOV;
}

void cam::setResolutionHorizontal(int resolutionHorizontal) {
    this->resolutionHorizontal = resolutionHorizontal;
}

void cam::setResolutionVertical(int resolutionVertical) {
    this->resolutionVertical = resolutionVertical;
}

void cam::setMaxBounces(int maxBounces) {
    this->maxBounces = maxBounces;
}

#endif