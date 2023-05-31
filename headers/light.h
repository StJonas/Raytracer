#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"

class light {
public:
    // Constructors
    light() {};
    light(const vec3& color, const vec3& direction)
    : color(color), direction(direction) {};
    light(const vec3& backgroundColor, const vec3& color, const vec3& direction)
    : backgroundColor(backgroundColor), color(color), direction(direction) {};

    // Getter methods
    vec3 getBackgroundColor() const;
    vec3 getColor() const;
    vec3 getDirection() const;

    // Setter methods
    void setBackgroundColor(const vec3& backgroundColor);
    void setColor(const vec3& color);
    void setDirection(const vec3& direction);

    vec3 backgroundColor;
    vec3 color;
    vec3 direction;
};

vec3 light::getBackgroundColor() const {
    return backgroundColor;
}

vec3 light::getColor() const {
    return color;
}

vec3 light::getDirection() const {
    return direction;
}

void light::setBackgroundColor(const vec3& newBackgroundColor) {
    backgroundColor = newBackgroundColor;
}

void light::setColor(const vec3& newColor) {
    color = newColor;
}

void light::setDirection(const vec3& newDirection) {
    direction = newDirection;
}
#endif
