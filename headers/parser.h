#include <iostream>
#include <fstream>
#include "../pugixml/pugixml.hpp"
#include "sphere_object.h"
#include "cam.h"
#include "light.h"

struct SceneData {
    cam cameraObj;
    std::vector<light> lightObjects;
    std::vector<sphere_object> sphereObjects;
};

SceneData parseXML(const std::string& xmlFilePath)
{
    SceneData scene;
    // Load the XML document from a file
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xmlFilePath.c_str());
    //pugi::xml_parse_result result = doc.load_file("./scenes/example3.xml");

    // Check if the XML document was loaded successfully
    if (!result)
    {
        std::cout << "XML parsing error: " << result.description() << std::endl;
        //return;
    }

    // // Open the output file
     std::ofstream outputFile("output.txt");
    if (!outputFile.is_open())
    {
        std::cout << "Failed to open output file." << std::endl;
        //return;
    }

    // Access elements and attributes in the XML document
    pugi::xml_node root = doc.child("scene");

    light lightObject;
    pugi::xml_node bCNode = root.child("background_color");
    double bCR = bCNode.attribute("r").as_double();
    double bCG = bCNode.attribute("g").as_double();
    double bCB = bCNode.attribute("b").as_double();
    vector bC(bCR, bCG, bCB);
    lightObject.setBackgroundColor(bC);

    for (pugi::xml_node cameraNode : root.children("camera"))
    {
        // Access the attributes of the cam node
        pugi::xml_node positionNode = cameraNode.child("position");
        double positionx = positionNode.attribute("x").as_double();
        double positiony = positionNode.attribute("y").as_double();
        double positionz = positionNode.attribute("z").as_double();
        vector position(positionx, positiony, positionz);

        pugi::xml_node lookatNode = cameraNode.child("lookat");
        double lookatx = lookatNode.attribute("x").as_double();
        double lookaty = lookatNode.attribute("y").as_double();
        double lookatz = lookatNode.attribute("z").as_double();
        vector lookat(lookatx, lookaty, lookatz);

        pugi::xml_node upNode = cameraNode.child("up");
        double upx = upNode.attribute("x").as_double();
        double upy = upNode.attribute("y").as_double();
        double upz = upNode.attribute("z").as_double();
        vector up(upx, upy, upz);

        double horizontal_fov = cameraNode.child("horizontal_fov").attribute("angle").as_double();
        int resolution_horizontal = cameraNode.child("resolution").attribute("horizontal").as_int();
        int resolution_vertical = cameraNode.child("resolution").attribute("vertical").as_int();
        int max_bounces = cameraNode.child("max_bounces").attribute("n").as_int();

        scene.cameraObj.setPosition(position);
        scene.cameraObj.setLookAt(lookat);
        scene.cameraObj.setUp(up);
        scene.cameraObj.setHorizontalFOV(horizontal_fov);
        scene.cameraObj.setResolutionHorizontal(resolution_horizontal);
        scene.cameraObj.setResolutionVertical(resolution_vertical);
        scene.cameraObj.setMaxBounces(max_bounces);

        // Print
        // std::cout << "cam Attributes:" << std::endl;
        // std::cout << "Position: " << positionx << ", " << positiony << ", " << positionz << std::endl;
        // std::cout << "Lookat: " << lookatx << ", " << lookaty << ", " << lookatz << std::endl;
        // std::cout << "Up: " << upx << ", " << upy << ", " << upz << std::endl;
        // std::cout << "Horizontal FOV: " << horizontal_fov << std::endl;
        // std::cout << "Resolution (Horizontal): " << resolution_horizontal << std::endl;
        // std::cout << "Resolution (Vertical): " << resolution_vertical << std::endl;
        // std::cout << "Max Bounces: " << max_bounces << std::endl;
    }

    pugi::xml_node lightsNode = root.child("lights");

    // Loop over each light node
    for (pugi::xml_node lightNode : lightsNode.children())
    {
        std::string lightType = lightNode.name();

        if (lightType == "ambient_light")
        {
            // Retrieve the color attributes of the ambient_light node
            pugi::xml_node colorNode = lightNode.child("color");
            double ambientLightR = colorNode.attribute("r").as_double();
            double ambientLightG = colorNode.attribute("g").as_double();
            double ambientLightB = colorNode.attribute("b").as_double();
            vector color(ambientLightR, ambientLightG, ambientLightB);
            lightObject.setColor(color);
            vector direction(0.0, 0.0, 0.0);
            lightObject.setDirection(direction);
            lightObject.setType(light::AMBIENT);

            //print
            // std::cout << "ambient_light:" << std::endl;
            // std::cout << "ambientLight color: " << std::endl;
            // std::cout << "Color: " << ambientLightR << ", " << ambientLightG << ", " << ambientLightB << std::endl;
        }
        else if (lightType == "parallel_light")
        {
            // Retrieve the color attributes of the parallel_light node
            pugi::xml_node colorNode = lightNode.child("color");
            double parallelLightR = colorNode.attribute("r").as_double();
            double parallelLightG = colorNode.attribute("g").as_double();
            double parallelLightB = colorNode.attribute("b").as_double();
            vector color(parallelLightR, parallelLightG, parallelLightB);
            lightObject.setColor(color);

            // Retrieve the direction attributes of the parallel_light node
            pugi::xml_node directionNode = lightNode.child("direction");
            double parallelLightDirectionX = directionNode.attribute("x").as_double();
            double parallelLightDirectionY = directionNode.attribute("y").as_double();
            double parallelLightDirectionZ = directionNode.attribute("z").as_double();
            vector direction(parallelLightDirectionX, parallelLightDirectionY, parallelLightDirectionZ);
            lightObject.setDirection(direction);
            lightObject.setType(light::PARALLEL);
            //print
            // std::cout << "parallel_light:" << std::endl;
            // std::cout << "ambientLight color: " << std::endl;
            // std::cout << "Color: " << parallelLightR << ", " << parallelLightG << ", " << parallelLightB << std::endl;
            // std::cout << "direction: " << parallelLightDirectionX << ", " << parallelLightDirectionY << ", " << parallelLightDirectionZ << std::endl;
        }
        else if (lightType == "point_light")
        {
            // Retrieve the color attributes of the parallel_light node
            pugi::xml_node colorNode = lightNode.child("color");
            double parallelLightR = colorNode.attribute("r").as_double();
            double parallelLightG = colorNode.attribute("g").as_double();
            double parallelLightB = colorNode.attribute("b").as_double();
            vector color(parallelLightR, parallelLightG, parallelLightB);
            lightObject.setColor(color);

            // Retrieve the direction attributes of the parallel_light node
            pugi::xml_node positionNode = lightNode.child("position");
            double parallelLightDirectionX = positionNode.attribute("x").as_double();
            double parallelLightDirectionY = positionNode.attribute("y").as_double();
            double parallelLightDirectionZ = positionNode.attribute("z").as_double();
            vector position(parallelLightDirectionX, parallelLightDirectionY, parallelLightDirectionZ);
            lightObject.setPosition(position);
            lightObject.setType(light::PARALLEL);
            //print
            // std::cout << "parallel_light:" << std::endl;
            // std::cout << "ambientLight color: " << std::endl;
            // std::cout << "Color: " << parallelLightR << ", " << parallelLightG << ", " << parallelLightB << std::endl;
            // std::cout << "direction: " << parallelLightDirectionX << ", " << parallelLightDirectionY << ", " << parallelLightDirectionZ << std::endl;
        }
        scene.lightObjects.push_back(lightObject);
    }

    pugi::xml_node surfacesNode = root.child("surfaces");
    double counter = 0;
    for (pugi::xml_node sphereNode : surfacesNode.children("sphere"))
    {
        counter++;
        //std::cout << "Object nr: " << counter << std::endl;

        //sphere_object
        double sphereRadius = sphereNode.attribute("radius").as_double();
        pugi::xml_node positionNode = sphereNode.child("position");
        double spherePositionX = positionNode.attribute("x").as_double();
        double spherePositionY = positionNode.attribute("y").as_double();
        double spherePositionZ = positionNode.attribute("z").as_double();
        vector position(spherePositionX, spherePositionY, spherePositionZ);

        sphere_object sphereObject;
        sphereObject.setPosition(position);
        sphereObject.setRadius(sphereRadius);

        // MATERIAL
        pugi::xml_node materialSolidNode = sphereNode.child("material_solid");
        pugi::xml_node materialColorNode = materialSolidNode.child("color");
        double sphereColorR = materialColorNode.attribute("r").as_double();
        double sphereColorG = materialColorNode.attribute("g").as_double();
        double sphereColorB = materialColorNode.attribute("b").as_double();
        pugi::xml_node phongNode = materialSolidNode.child("phong");
        double phongKA = phongNode.attribute("ka").as_double();
        double phongKD = phongNode.attribute("kd").as_double();
        double phongKS = phongNode.attribute("ks").as_double();
        double phongExponent = phongNode.attribute("exponent").as_double();
        double reflectanceR = materialSolidNode.child("reflectance").attribute("r").as_double();
        double transmittanceT = materialSolidNode.child("transmittance").attribute("t").as_double();
        double refractionIOF = materialSolidNode.child("refraction").attribute("iof").as_double();
        vector materialColor(sphereColorR, sphereColorG, sphereColorB);
        vector phong(phongKA, phongKD,phongKS);
        sphereObject.setMaterialColor(materialColor);
        sphereObject.setPhong(phong);
        sphereObject.setPhongExponent(phongExponent);
        sphereObject.setReflectance(reflectanceR);
        sphereObject.setTransmittance(transmittanceT);
        sphereObject.setRefraction(refractionIOF);
        scene.sphereObjects.push_back(sphereObject);

        //Create a SphereData object and fill it with the retrieved data
        // std::cout << "surfaces:" << std::endl;
        //std::cout << "sphereRadius: " << sphereRadius << std::endl;
        // std::cout << "position: " << spherePositionX << ", " << spherePositionY << ", " << spherePositionZ << std::endl;
        // std::cout << "material_solid:" << std::endl;
        // std::cout << "color: " << std::endl;
        // std::cout << sphereColorR << ", " << sphereColorG << ", " << sphereColorB << std::endl;
        // std::cout << "phong: " << std::endl;
        // std::cout << phongKA << ", " << phongKD << ", " << phongKS << phongExponent << std::endl;
        // std::cout << "reflectanceR: " << reflectanceR << std::endl;
        // std::cout << "transmittanceT: " << transmittanceT << std::endl;
        // std::cout << "refractionIOF: " << refractionIOF << std::endl;
    }


    outputFile.close();

    return scene;
}
