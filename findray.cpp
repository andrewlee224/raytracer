#include <iostream>
#include "findray.h"
#include "variables.h"

void construct_orth_coord_frame(const vec3 eye, const vec3 center, const vec3 up,
        vec3 &w, vec3 &u, vec3 &v) {
    vec3 a = eye - center;
    w = glm::normalize(a);
    u = glm::normalize(glm::cross(up, w));
    v = glm::cross(w, u);
}

vec3 find_ray_thru_pixel(vec3 eye, vec3 center, vec3 up, 
        int fovx, int fovy, float i, float j) {

    vec3 u, v, w;

    construct_orth_coord_frame(eye, center, up, w, u, v);

    std::cout << "Created eye coordinate frame: " << std::endl;
    std::cout << glm::to_string(w) << std::endl << glm::to_string(u) << std::endl 
        << glm::to_string(v) << std::endl;

    float alpha = glm::tan(glm::radians(fovx)/2) * ((i - WIDTH/2)/(WIDTH/2));
    float beta = glm::tan(glm::radians(fovy/2)) * (((HEIGHT/2) - j)/(HEIGHT/2));

    vec3 screen_coord = glm::normalize(alpha*u + beta*v - w);
    
    vec3 ray = eye + screen_coord;
    std::cout << "Computed normalized ray: " << glm::to_string(screen_coord) << std::endl;

    return screen_coord;
}
