#include "variables.h"

enum class ObjectType{Sphere, Triangle};

class GeomObject {
        ObjectType type;
        vec4 ambient;
        vec4 diffuse;
        vec4 specular;
        vec4 emission;
        float shininess;
        mat4 transform;
    public:
        GeomObject();
};
