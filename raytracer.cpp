#include <iostream>
#include "FreeImage.h"


int main(int argc, char* argv[]) {

    FreeImage_Initialise();
    std::cout << "FreeImage Version " << FreeImage_GetVersion() << std::endl;
    FreeImage_DeInitialise();

    return 0;
}
