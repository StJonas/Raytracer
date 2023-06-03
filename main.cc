#include "headers/color.h"
#include "headers/hittable_list.h"
#include "headers/sphere.h"
#include "headers/util.h"
#include "headers/camera.h"
#include "headers/light.h"
#include "headers/parser.h"
#include <iostream>

color ray_color(const ray& r, const hittable& world, const light& lightObj, int maxBounces) {
    hit_record rec;
    if (maxBounces <= 0)
        return lightObj.getBackgroundColor();

    if (world.hit(r, 0, infinity, rec)) {
        return rec.color;
    }

    return lightObj.getBackgroundColor();
}

int main() {
    SceneData sceneData = parseXML();

    camera& cameraObj = sceneData.cameraObj;
    light& lightObj = sceneData.lightObj;
    std::vector<sphere>& sphereObjects = sceneData.sphereObjects;

    const int image_width = cameraObj.getResolutionHorizontal();
    const int image_height = cameraObj.getResolutionVertical();
    const auto aspect_ratio = image_width/image_height;

    // World
    hittable_list world;
    for (const sphere& sphereObj : sceneData.sphereObjects) {
        world.add(make_shared<sphere>(sphereObj.getRadius(), sphereObj.getPosition(), sphereObj.getMaterialColor()));
        //std::cout << "Color: " << sphereObj.getMaterialColor();
    }

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 2.0;

    auto origin = cameraObj.getPosition();
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
    auto maxBounces = cameraObj.getMaxBounces();

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            //ray r(origin, lower_left_corner + horizontal + vertical);

            color pixel_color = ray_color(r, world, lightObj, maxBounces);
            write_color(std::cout, pixel_color);

            // if (i < cameraObj.getMaxBounces()) {
            //     color pixel_color = ray_color(r, world, lightObj);
            //     write_color(std::cout, pixel_color);
            // } else {
            //    color pixel_color = lightObj.getBackgroundColor(); // Assign a default color
            //    write_color(std::cout, pixel_color);
            // }
        }
    }

    std::cerr << "\nDone.\n";
}