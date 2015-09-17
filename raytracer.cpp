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
    //find_ray_thru_pixel(eye, center, up, 90, 90, 20.0, 20.0);
    
    FIBITMAP* bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BPP);
    RGBQUAD color;

    if (!bitmap) {
        exit(1);
    }

    Sphere sphere1(
            vec3(0.0, 0.0, 0.0), 2.0, 0);
    sphere1.diffuse = vec4(0.5, 0.0, 0.0, 1.0);
    
    int i, j;
    float x, y;
    for (j = 0; j < HEIGHT; j++) {
        for (i = 0; i < WIDTH; i++) {
            x = float(i) + 0.5;
            y = float(j) + 0.5;
            vec3 screen_ray = find_ray_thru_pixel(eye, center, up, FOVX, FOVY, x, y);
            
            // only one object for now
            Intersection intersection = sphere1.intersect(eye, screen_ray);

            if (intersection.found) {
                color.rgbRed = sphere1.diffuse[0] * 255.0;
                color.rgbGreen = sphere1.diffuse[1] * 255.0;
                color.rgbBlue = sphere1.diffuse[2] * 255.0;
            } else {
                color.rgbRed = 0.0;
                color.rgbGreen = 0.0;
                color.rgbBlue = 0.0;
            }

            //color.rgbRed = (double)i / WIDTH * 255.0;
            //color.rgbGreen = (double)j / HEIGHT * 255.0;
            //color.rgbBlue = 0;
            FreeImage_SetPixelColor(bitmap, i, j, &color);
        }
    }

    if (FreeImage_Save(FIF_PNG, bitmap, "test.png", 0)) {
        std::cout << "Image successfully saved!" << std::endl;
    }
    
    FreeImage_DeInitialise();

    return 0;
}
