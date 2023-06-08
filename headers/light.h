#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"
#include "object.h"
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
    light(const vector& color, const vector& direction)
    : color(color), direction(direction) {};
    light(const vector& backgroundColor, const vector& color, const vector& direction)
    : backgroundColor(backgroundColor), color(color), direction(direction) {};

    // Getter methods
    vector getBackgroundColor() const;
    vector getColor() const;
    vector getDirection() const;
    vector getPosition() const;

    // Setter methods
    void setBackgroundColor(const vector& backgroundColor);
    void setColor(const vector& color);
    void setDirection(const vector& direction);
    void setPosition(const vector& position);
    void setType(LightType light);

    vector calcFinalColor(light ambient, light parallel, intersection_record rec);
    vector calcShading(light parallel, intersection_record rec, const object& world);

    vector backgroundColor;
    vector color;
    vector direction;
    vector position;
    LightType lightType;

    LightType getType() const {
    return this->lightType;
    }  
};

vector light::getBackgroundColor() const {
    return backgroundColor;
}

vector light::getColor() const {
    return color;
}

vector light::getDirection() const {
    return direction;
}

void light::setBackgroundColor(const vector& newBackgroundColor) {
    this->backgroundColor = newBackgroundColor;
}

void light::setColor(const vector& newColor) {
    this->color = newColor;
}

void light::setDirection(const vector& newDirection) {
    this->direction = newDirection;
}

void light::setType(const LightType lightType) {
    this->lightType = lightType;
}

vector light::getPosition() const {
    return position;
}
void light::setPosition(const vector& newPosition) {
    this->position = newPosition;
}

vector light::calcFinalColor(light ambient, light pLight, intersection_record rec){
    vector finalColor;
    vector reflectionVector;
    if(pLight.getType()==light::PARALLEL){
        //reflectVector = v - 2 * dot(v, n) * n 
        reflectionVector = -unit_vector(pLight.getDirection()) - 2 * dot(-unit_vector(pLight.getDirection()), rec.normal) * rec.normal;
    } else{
        vector lightPosition = pLight.getPosition();
        vector lightDirection = -unit_vector(lightPosition - rec.p);
        reflectionVector = lightDirection - 2 * dot(lightDirection, rec.normal) * rec.normal;
    }

    //specular = reflectVector * viewDirection -> viewDirection = -ray direction
    double spec = pow(std::max(0.0, dot(-unit_vector(reflectionVector), -unit_vector(rec.r.direction()))), rec.phongE);
    vector specularComponent = pLight.getColor() * spec;
    
    //diffuse = lightColor * max(0, dot(surfaceNormal, lightDirection))
    vector diffuseComponent =  rec.color * std::max(0.0, dot(rec.normal, -unit_vector(pLight.getDirection())));
    vector finalDiffuse = diffuseComponent * pLight.getColor();

    vector finalAmbient = ambient.getColor()*rec.color;
    
    finalColor = finalAmbient*rec.phong.x() + finalDiffuse * rec.phong.y() + specularComponent*rec.phong.z() ;

    //std::cerr << "light pos: " << rec.p;
    return finalColor;
}

vector light::calcShading(light pLight, intersection_record rec, const object& world){
    vector shadowRayDirection = -unit_vector(pLight.getDirection());
    ray shadowRay(rec.p, shadowRayDirection);
    vector finalColor(0.0,0.0,0.0);
    intersection_record recNew;

    if (dot(rec.normal, shadowRayDirection) >= 0.0) {
        if (world.hit(shadowRay, 0.001, infinity, recNew)) {
        return this->getColor()*rec.color*rec.phong.x();
        }
    }

    return finalColor;
}

#endif