#include <iostream>
#include "FreeImage.h"

#include "variables.h"
#include "findray.h"
#include "objects.h"


int main(int argc, char* argv[]) {

    FreeImage_Initialise();

    std::cout << "FreeImage Version " << FreeImage_GetVersion() << std::endl;

    vec3 eye(0.0, 0.0, 3.0);
    vec3 center(0.0, 0.0, 0.0);
    vec3 up(0.0, 1.0, 0.0);
    
    FIBITMAP* bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BPP);
    RGBQUAD color;

    if (!bitmap) {
        exit(1);
    }

    // set up example scene
    Sphere sphere1(
            vec3(0.0, 0.0, 0.0), 2.5, 0);
    sphere1.ambient = vec4(0.5, 0.0, 0.0, 1.0);
    sphere1.specular = vec4(1.0, 1.0, 1.0, 1.0);
    sphere1.diffuse = vec4(1.0, 1.0, 1.0, 1.0);
    sphere1.shininess = 100;

    // light above sphere
    Light light1(
        vec4(1.0, 1.0, 3.0, 1.0),
        vec4(1.0, 1.0, 1.0, 1.0));

    Scene scene;
    GeomObject* object_arr[128];
    Light* light_arr[128];
    object_arr[0] = &sphere1;
    sphere1.scene_idx = 0;
    light_arr[0] = &light1;
    scene.object_arr = &object_arr[0];
    scene.light_arr = &light_arr[0];
    scene.used_objects = 1;
    scene.used_lights = 1;

    
    int i, j;
    float x, y;
    for (j = 0; j < HEIGHT; j++) {
        for (i = 0; i < WIDTH; i++) {
            x = float(i) + 0.5;
            y = float(j) + 0.5;
            vec3 screen_ray = find_ray_thru_pixel(eye, center, up, FOVX, FOVY, x, y);
            
            Intersection intersection = find_intersection(scene, eye, screen_ray);

            if (intersection.found) {
                vec4 found_color = find_color(scene, intersection, eye);
                color.rgbRed = found_color[2] * 255.0;
                color.rgbGreen = found_color[1] * 255.0;
                color.rgbBlue = found_color[0] * 255.0;
            } else {
                color.rgbRed = 0.0;
                color.rgbGreen = 0.0;
                color.rgbBlue = 0.0;
            }

            FreeImage_SetPixelColor(bitmap, i, j, &color);
        }
    }

    if (FreeImage_Save(FIF_PNG, bitmap, "test.png", 0)) {
        std::cout << "Image successfully saved!" << std::endl;
    }
    
    FreeImage_DeInitialise();

    return 0;
}
