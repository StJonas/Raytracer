#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"
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
    vec3 calcShading();

    vec3 backgroundColor;
    vec3 color;
    vec3 direction;
    bool isAmbient;

    //         vec3 nTransformedNormal = normalize(transformedNormal);
    //         vec3 lightColor = vec3(1.0, 1.0, 1.0);
    //         vec3 lightVector = normalize(vLightPosition.xyz - vViewPosition.xyz); 
    //         float lightIntensity = max(dot(lightVector, nTransformedNormal), 0.0);

    //         float diffuseIntensity = 0.5;
    //         vec4 diffuseColor = vec4(vVertexColor.rgb * lightIntensity, 1.0);
    //         vec4 ambientColor = vec4(ambientLightColor, 1.0) * ambientReflection;
    //         vec4 diffuse = diffuseColor * diffuseIntensity;

    //         vec3 viewDirection = normalize(-vViewPosition.xyz);
    //         vec3 halfwayDirection = normalize(lightVector + viewDirection);
    //         float specularIntensity = pow(max(dot(nTransformedNormal, halfwayDirection), 0.0), shininess);
    //         vec3 spec = specularColor.rgb * specularReflection;
    //         vec4 final_specular = vec4(spec, 1.0) * specularIntensity;

    //         vec4 finalColor = diffuseColor + final_specular; (+ambient)
    //         final_specular.a = 1.0;
    //         gl_FragColor = finalColor;
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

// let v = -ray.dir.unit_vector();
//         let reflect = 2. * &light_direction.dot(normal)
//             * normal
//             - &light_direction;
//         let spec = reflect
//             .unit_vector()
//             .dot(&v)
//             .max(0.)
//             .powf(phong.exponent);
//         let specular = &self.color * spec;

vec3 light::calcShading(){
    // ich muss quasi vom intersection point einen ray zur light source erstellen, und wenn dann da was dazwischen ist, 
    // dann wird die fläche geshaded
    return vec3(0,0,0);
}

#endif