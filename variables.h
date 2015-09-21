#ifndef VARIABLES_H
#define VARIABLES_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"


typedef glm::mat3 mat3;
typedef glm::mat4 mat4;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;

const int WIDTH = 640;
const int HEIGHT = 480;
const int FOVX = 160;
const int FOVY = 155;
const int BPP = 24;

// for float operation approximations
const float EPSILON = 0.0001;
#endif
