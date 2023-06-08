#include "headers/color.h"
#include "headers/hittable_list.h"
#include "headers/sphere.h"
#include "headers/util.h"
#include "headers/camera.h"
#include "headers/light.h"
#include "headers/parser.h"
#include <iostream>

color ray_color(const ray& r, const hittable& world, light& ambientLight, light& pLight, int maxBounces) {
    hit_record rec;
    hit_record recShader;
    if (maxBounces <= 0)
        return ambientLight.getBackgroundColor();

    if (world.hit(r, 0.001, infinity, rec)) {
        recShader.color = ambientLight.calcShading(pLight, rec, world);
        if(recShader.color == vec3(0.0,0.0,0.0)){
            rec.color = ambientLight.calcFinalColor(ambientLight, pLight, rec);
            ray_color(r, world, ambientLight, pLight, maxBounces-1);
            return rec.color;
        }
        
        return recShader.color;
    }

    return ambientLight.getBackgroundColor();
}

int main(int argc, char* argv[]) {
    std::string xmlFilePath = argv[1];
    //std::string outputFilePath = "image.ppm";
    std::filesystem::path inputFile(xmlFilePath);
    std::string outputFilePath = inputFile.stem().string() + ".ppm";
    SceneData sceneData = parseXML(xmlFilePath);
    //SceneData sceneData = parseXML();

    camera& cameraObj = sceneData.cameraObj;
    std::vector<light>& lightObjects = sceneData.lightObjects;
    light ambientLight(vec3(0,0,0), vec3(0,0,0));
    light pLight(vec3(0,0,0), vec3(0,0,0));
    std::vector<sphere>& sphereObjects = sceneData.sphereObjects;

    const int image_width = cameraObj.getResolutionHorizontal();
    const int image_height = cameraObj.getResolutionVertical();
    const auto aspect_ratio = image_width/image_height;

    for (const light& lightObj : sceneData.lightObjects) {
        if (lightObj.getType() == light::AMBIENT) {
            ambientLight = lightObj;
        }
        if(lightObj.getType() == light::PARALLEL) {
            pLight = lightObj;
        } else {
            pLight = lightObj;
        }
    }

    // World
    hittable_list world;
    for (const sphere& sphereObj : sceneData.sphereObjects) {
        world.add(make_shared<sphere>(sphereObj.getRadius(), sphereObj.getPosition(), sphereObj.getMaterialColor(), sphereObj.getPhong(), sphereObj.getPhongExponent()));
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
    std::ofstream outputFile(outputFilePath);  // Open the output file
    outputFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {

            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);

            color pixel_color = ray_color(r, world, ambientLight, pLight, maxBounces);
            if (pixel_color.x() > 1) {
                pixel_color = vec3(0.999, pixel_color.y(), pixel_color.z());
            }
            if (pixel_color.y() > 1) {
                pixel_color = vec3(pixel_color.x(), 0.999, pixel_color.z());
            }
            if (pixel_color.z() > 1) {
                pixel_color = vec3(pixel_color.x(), pixel_color.y(), 0.999);
            }
            write_color(outputFile, pixel_color);
        }
    }
    outputFile.close();  // Close the output file
    std::cerr << "\nDone.\n";

}