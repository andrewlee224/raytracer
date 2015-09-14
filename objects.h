#include "variables.h"


enum class ObjectType{Sphere, Triangle};

class Intersection {
        int found;
        vec4 position;
        vec4 normal;
    public:
        Intersection(int found, vec4 position, vec4 normal);
};

class GeomObject {
    public:
        GeomObject();
        virtual Intersection intersect(vec4 eye, vec4 screen_ray) = 0;  // every child class has to implement this
};


class Sphere: public GeomObject {
        ObjectType type;
        vec4 ambient;
        vec4 diffuse;
        vec4 specular;
        vec4 emission;
        float shininess;
        mat4 transform;
        vec4 center;
        float radius;
    public:
        Sphere(
            vec4 ambient, vec4 diffuse, vec4 specular, vec4 emission, vec4 center, float radius);
        virtual Intersection intersect(vec4 eye, vec4 screen_ray);
};

class Triangle: public GeomObject {
        ObjectType type;
        vec4 ambient;
        vec4 diffuse;
        vec4 specular;
        vec4 emission;
        float shininess;
        mat4 transform;
        vec4 vert1;
        vec4 vert2;
        vec4 vert3;
    public:
        Triangle(
            vec4 ambient, vec4 diffuse, vec4 specular, vec4 emission, vec4 center,
            vec4 vert1, vec4 vert2, vec4 vert3);
        virtual Intersection intersect(vec4 eye, vec4 screen_ray);

};
