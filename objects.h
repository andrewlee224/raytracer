#ifndef OBJECTS_H
#define OBJECTS_H

#include "variables.h"


enum class ObjectType{Sphere, Triangle};


struct Light {
    vec4 position;
    vec4 color;
};


struct Intersection {
    int found;
    vec3 position;
    vec3 normal;
    int hit_object_idx;
    Intersection(int found, vec3 position, vec3 normal);
};


struct GeomObject {
    ObjectType type;
    int scene_idx;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 emission;
    float shininess;
    mat4 transform;
    GeomObject();
    GeomObject(int scene_idx);
    virtual Intersection intersect(vec3 eye, vec3 screen_ray) = 0;  // every child class has to implement this
};


struct Sphere: public GeomObject {
    ObjectType type;
    vec3 center;
    float radius;
    Sphere(
        vec3 center, float radius, int scene_idx);
    virtual Intersection intersect(vec3 eye, vec3 screen_ray);
};

struct Triangle: public GeomObject {
    vec3 vert1;
    vec3 vert2;
    vec3 vert3;
    Triangle(
        vec3 vert1, vec3 vert2, vec3 vert3);
    virtual Intersection intersect(vec3 eye, vec3 screen_ray);
};


struct Scene {
    GeomObject* object_arr[128];
    Light* light_arr[128];
    int used_objects;
    int used_lights;
};


#endif
