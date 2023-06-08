#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"
#include "hittable.h"
#include <algorithm>
#include <cmath>

class light {
public:
    enum LightType {
        AMBIENT,
        PARALLEL,
        POINT
    };

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
    vec3 getPosition() const;

    // Setter methods
    void setBackgroundColor(const vec3& backgroundColor);
    void setColor(const vec3& color);
    void setDirection(const vec3& direction);
    void setPosition(const vec3& position);
    void setType(LightType light);

    vec3 calcFinalColor(light ambient, light parallel, hit_record rec);
    vec3 calcShading(light parallel, hit_record rec, const hittable& world);

    vec3 backgroundColor;
    vec3 color;
    vec3 direction;
    vec3 position;
    LightType lightType;

    LightType getType() const {
    return this->lightType;
    }  
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

void light::setType(const LightType lightType) {
    this->lightType = lightType;
}

vec3 light::getPosition() const {
    return position;
}
void light::setPosition(const vec3& newPosition) {
    this->position = newPosition;
}

vec3 light::calcFinalColor(light ambient, light pLight, hit_record rec){
    vec3 finalColor;
    vec3 reflectionVector;
    if(pLight.getType()==light::PARALLEL){
        //reflectVector = v - 2 * dot(v, n) * n 
        reflectionVector = -unit_vector(pLight.getDirection()) - 2 * dot(-unit_vector(pLight.getDirection()), rec.normal) * rec.normal;
    } else{
        vec3 lightPosition = pLight.getPosition();
        vec3 lightDirection = -unit_vector(lightPosition - rec.p);
        reflectionVector = lightDirection - 2 * dot(lightDirection, rec.normal) * rec.normal;
    }

    //specular = reflectVector * viewDirection -> viewDirection = -ray direction
    double spec = pow(std::max(0.0, dot(-unit_vector(reflectionVector), -unit_vector(rec.r.direction()))), rec.phongE);
    vec3 specularComponent = pLight.getColor() * spec;
    
    //diffuse = lightColor * max(0, dot(surfaceNormal, lightDirection))
    vec3 diffuseComponent =  rec.color * std::max(0.0, dot(rec.normal, -unit_vector(pLight.getDirection())));
    vec3 finalDiffuse = diffuseComponent * pLight.getColor();

    vec3 finalAmbient = ambient.getColor()*rec.color;
    
    finalColor = finalAmbient*rec.phong.x() + finalDiffuse * rec.phong.y() + specularComponent*rec.phong.z() ;

    //std::cerr << "light pos: " << rec.p;
    return finalColor;
}

vec3 light::calcShading(light pLight, hit_record rec, const hittable& world){
    vec3 shadowRayDirection = -unit_vector(pLight.getDirection());
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