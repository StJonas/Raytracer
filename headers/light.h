#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"
#include "hittable.h"
#include <algorithm>
#include <cmath>

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
    bool getIsAmbient() const;

    // Setter methods
    void setBackgroundColor(const vec3& backgroundColor);
    void setColor(const vec3& color);
    void setDirection(const vec3& direction);
    void setIsAmbient(const bool isAmbient);

    vec3 calcFinalColor(light ambient, light parallel, hit_record rec);
    vec3 calcShading(light parallel, hit_record rec, const hittable& world);

    vec3 backgroundColor;
    vec3 color;
    vec3 direction;
    bool isAmbient;
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
    this->backgroundColor = newBackgroundColor;
}

void light::setColor(const vec3& newColor) {
    this->color = newColor;
}

void light::setDirection(const vec3& newDirection) {
    this->direction = newDirection;
}

bool light::getIsAmbient() const {
    return isAmbient;
}
void light::setIsAmbient(const bool isAmbient) {
    this->isAmbient = isAmbient;
}

vec3 light::calcFinalColor(light ambient, light parallel, hit_record rec){
    //reflectVector = v - 2 * dot(v, n) * n 
    vec3 reflectionVector = -unit_vector(parallel.getDirection()) - 2 * dot(-unit_vector(parallel.getDirection()), rec.normal) * rec.normal;
    //specular = reflectVector * viewDirection -> viewDirection = -ray direction
    double spec = pow(std::max(0.0, dot(-unit_vector(reflectionVector), -unit_vector(rec.r.direction()))), rec.phongE);
    vec3 specularComponent = parallel.getColor() * spec;
    //diffuse = lightColor * max(0, dot(surfaceNormal, lightDirection))
    vec3 diffuseComponent =  rec.color * std::max(0.0, dot(rec.normal, -unit_vector(parallel.getDirection())));
    vec3 finalDiffuse = diffuseComponent * parallel.getColor();

    vec3 finalAmbient = ambient.getColor()*rec.color;

    vec3 finalColor;
    finalColor = finalAmbient*rec.phong.x() + finalDiffuse * rec.phong.y() + specularComponent*rec.phong.z() ;
   
    return finalColor;
}

vec3 light::calcShading(light parallel, hit_record rec, const hittable& world){
    vec3 shadowRayDirection = -unit_vector(parallel.getDirection());
    ray shadowRay(rec.p, shadowRayDirection);
    vec3 finalColor(0.0,0.0,0.0);
    hit_record recNew;

    if (dot(rec.normal, shadowRayDirection) >= 0.0) {
        if (world.hit(shadowRay, 0.001, infinity, recNew)) {
        return this->getColor()*rec.color*rec.phong.x();
        }
    }

    return finalColor;
}

#endif