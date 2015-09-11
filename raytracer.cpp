#include <iostream>
#include "FreeImage.h"

#include "variables.h"
#include "findray.h"


int main(int argc, char* argv[]) {

    FreeImage_Initialise();
    std::cout << "FreeImage Version " << FreeImage_GetVersion() << std::endl;

    vec3 eye(2.0, 2.0, 1.0);
    vec3 center(3.0, 5.0, 0.0);
    vec3 up(0.0, 0.0, 1.0);
    find_ray_thru_pixel(eye, center, up, 90, 90, 20.0, 20.0);
    
    FIBITMAP* bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BPP);
    RGBQUAD color;

    if (!bitmap) {
        exit(1);
    }
    
    int i, j;
    for (j = 0; j < HEIGHT; j++) {
        for (i = 0; i < WIDTH; i++) {
            color.rgbRed = (double)i / WIDTH * 255.0;
            color.rgbGreen = (double)j / HEIGHT * 255.0;
            color.rgbBlue = 0;
            FreeImage_SetPixelColor(bitmap, i, j, &color);
        }
    }

    if (FreeImage_Save(FIF_PNG, bitmap, "test.png", 0)) {
        std::cout << "Image successfully saved!" << std::endl;
    }
    
    FreeImage_DeInitialise();

    return 0;
}
