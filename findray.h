#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"

#include "objects.h"


typedef glm::mat3 mat3;
typedef glm::mat4 mat4;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;


vec3 find_ray_thru_pixel(vec3 eye, vec3 center, vec3 up,
        int fovx, int fovy, float i, float j);

Intersection find_intersection(Scene scene, vec3 eye, vec3 screen_ray);

vec4 find_color(Scene scene, Intersection intersection, vec3 pov);
