#ifndef SPHEREOBJECT_H
#define SPHEREOBJECT_H

#include "vector.h"
#include "object.h"

class sphere_object : public object {
    public:
        sphere_object() {};
        sphere_object(point3 cen, double r) : center(cen), radius(r) {};
        sphere_object(double radius, const vector& position) : center(position), radius(radius) {};
        sphere_object(double radius, const vector& position, const vector& color, const vector& phong, const double phongE) : 
        center(position), radius(radius), color(color), phong(phong), phongExponent(phongE) {};

        virtual bool hit(
            const ray& r, double t_min, double t_max, intersection_record& rec) const override;

    public:
        point3 center;
        double radius;
        vector color;
        vector phong;
        double phongExponent;
        double reflectance;
        double transmittance;
        double refraction;

        double getRadius() const;
        vector getPosition() const;
        vector getMaterialColor() const;
        vector getPhong() const;
        double getPhongKA() const;
        double getPhongExponent() const;
        double getReflectance() const;
        double getTransmittance() const;
        double getRefraction() const;

        // Setter methods
        void setRadius(double& radius);
        void setPosition(const vector& position);
        void setMaterialColor(const vector& color);
        void setPhong(const vector& phong);
        void setPhongExponent(const double& exponent);
        void setReflectance(const double& reflectance);
        void setTransmittance(const double& transmittance);
        void setRefraction(const double& refraction);
};

void sphere_object::setPosition(const vector& position) {
    this->center = position;
}
vector sphere_object::getPosition() const {
    return center;
}

void sphere_object::setMaterialColor(const vector& color) {
    this->color = color;
}
vector sphere_object::getMaterialColor() const {
    return color;
}

void sphere_object::setRadius(double& radius) {
    this->radius = radius;
}
double sphere_object::getRadius() const {
    return radius;
}

void sphere_object::setPhong(const vector& phong) {
    this->phong = phong;
}
vector sphere_object::getPhong() const {
    return phong;
}
double sphere_object::getPhongKA() const {
    return phong.x();
}


void sphere_object::setPhongExponent(const double& phongExponent) {
    this->phongExponent = phongExponent;
}
double sphere_object::getPhongExponent() const {
    return phongExponent;
}

void sphere_object::setReflectance(const double& reflectance) {
    this->reflectance = reflectance;
}
double sphere_object::getReflectance() const {
    return reflectance;
}

void sphere_object::setTransmittance(const double& transmittance) {
    this->transmittance = transmittance;
}
double sphere_object::getTransmittance() const {
    return transmittance;
}

void sphere_object::setRefraction(const double& refraction) {
    this->refraction = refraction;
}
double sphere_object::getRefraction() const {
    return refraction;
}

bool sphere_object::hit(const ray& r, double t_min, double t_max, intersection_record& rec) const {
    vector oc = r.origin() - center;
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
    vector outward_normal = (rec.p - center) / radius;
    rec.normal = (rec.p - center) / radius;
    rec.phong=this->getPhong();
    rec.phongE=this->getPhongExponent();
    rec.r = r;

    rec.color = this->getMaterialColor(); 

    return true;
}

std::ostream& operator<<(std::ostream& os, const sphere_object& sphereObj) {
        os << "sphere_object Object: (Center: " << sphereObj.center << ", Radius: " << sphereObj.radius << ")";
        return os;
    }

#endif