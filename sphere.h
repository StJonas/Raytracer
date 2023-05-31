#ifndef SURFACE_H
#define SURFACE_H

#include "headers/vec3.h"
#include "headers/material.h"

class Surface
{
public:
    // Constructors
    Surface();
    Surface(double radius, const vec3 &position, const material &material);

    // Getter methods
    double getRadius() const;
    vec3 getPosition() const;
    material getMaterial() const;

    // Setter methods
    void setRadius(double radius);
    void setPosition(const vec3 &position);
    void setMaterial(const material &material);

private:
    double radius_;
    material position_;
    material material_;
};

#endif // SURFACE_H
