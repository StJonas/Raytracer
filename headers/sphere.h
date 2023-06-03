#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "hittable.h"

class sphere : public hittable {
    public:
        sphere() {};
        sphere(point3 cen, double r) : center(cen), radius(r) {};
        sphere(double radius, const vec3& position) : center(position), radius(radius) {};
        sphere(double radius, const vec3& position, const vec3& color) : center(position), radius(radius), color(color) {};

        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        point3 center;
        double radius;
        vec3 color;
        vec3 phong;
        double phongExponent;
        double reflectance;
        double transmittance;
        double refraction;

        double getRadius() const;
        vec3 getPosition() const;
        vec3 getMaterialColor() const;
        vec3 getPhong() const;
        double getPhongExponent() const;
        double getReflectance() const;
        double getTransmittance() const;
        double getRefraction() const;

        // Setter methods
        void setRadius(double& radius);
        void setPosition(const vec3& position);
        void setMaterialColor(const vec3& color);
        void setPhong(const vec3& phong);
        void setPhongExponent(const double& exponent);
        void setReflectance(const double& reflectance);
        void setTransmittance(const double& transmittance);
        void setRefraction(const double& refraction);
};

void sphere::setPosition(const vec3& position) {
    this->center = position;
}
vec3 sphere::getPosition() const {
    return center;
}

void sphere::setMaterialColor(const vec3& color) {
    this->color = color;
}
vec3 sphere::getMaterialColor() const {
    return color;
}

void sphere::setRadius(double& radius) {
    this->radius = radius;
}
double sphere::getRadius() const {
    return radius;
}

void sphere::setPhong(const vec3& phong) {
    this->phong = phong;
}
vec3 sphere::getPhong() const {
    return phong;
}

void sphere::setPhongExponent(const double& phongExponent) {
    this->phongExponent = phongExponent;
}
double sphere::getPhongExponent() const {
    return phongExponent;
}

void sphere::setReflectance(const double& reflectance) {
    this->reflectance = reflectance;
}
double sphere::getReflectance() const {
    return reflectance;
}

void sphere::setTransmittance(const double& transmittance) {
    this->transmittance = transmittance;
}
double sphere::getTransmittance() const {
    return transmittance;
}

void sphere::setRefraction(const double& refraction) {
    this->refraction = refraction;
}
double sphere::getRefraction() const {
    return refraction;
}

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.normal = (rec.p - center) / radius;
    rec.color = this->getMaterialColor(); 
    //std::cout << "Color: " << this->getMaterialColor();

    return true;
}

std::ostream& operator<<(std::ostream& os, const sphere& sphereObj) {
        os << "Sphere Object: (Center: " << sphereObj.center << ", Radius: " << sphereObj.radius << ")";
        return os;
    }

#endif