#include "objects.h"


Intersection::Intersection(int found, vec3 position, vec3 normal): 
    found(found), position(position), normal(normal)
{}

Light::Light() 
{}

Light::Light(vec4 position, vec4 color): position(position), color(color)
{}

GeomObject::GeomObject() 
{}

GeomObject::GeomObject(int scene_idx): scene_idx(scene_idx)
{}

Sphere::Sphere(
        vec3 center, float radius, int scene_idx): 
    GeomObject(scene_idx), center(center), radius(radius)
{}


Intersection Sphere::intersect(vec3 eye, vec3 screen_ray) {

    int found = 0;
    vec3 intersection_pos(1.0);
    vec3 normal(1.0);
    float t = 0.0;
    // solve the quadratic equation for t-parameter which
    // scales the ray vector (not eye+ray vector!)

    float a = glm::dot(screen_ray, screen_ray);
    float b = 2 * glm::dot(screen_ray, (eye - center));
    float c = glm::dot((eye - center), (eye - center)) - radius*radius;

    float delta = b*b - 4*a*c;

    if (delta < -EPSILON) {
        // no intersection found
        return Intersection(found, intersection_pos, normal);
    }

    if ((delta < EPSILON) && (delta > -EPSILON)) {
        delta = 0.0;
    }

    float delta_sqrt = glm::sqrt(delta);

    float t1 = (-b - delta_sqrt)/(2*a);
    float t2 = (-b + delta_sqrt)/(2*a);

    if (glm::abs(t1 - t2) < EPSILON) {
        // both solutions the same, ray tangent to the sphere
        // treat as no intersection
        return Intersection(found, intersection_pos, normal);
    }

    if (glm::max(t1, t2) < -EPSILON) {
        // both intersections behind the eye viewpoint
        return Intersection(found, intersection_pos, normal);
    }

    if ((t1 > EPSILON) && (t2 < -EPSILON)) {
        // one intersection in front of viewpoint, another behind
        // choose the one in front
        found = 1;
        t = t1;
    }
    else if ((t1 < -EPSILON) && (t2 > EPSILON)) {
        // as above
        found = 1;
        t = t2;
    }
    else if ((t1 > EPSILON) && (t2 > EPSILON)) {
        // two intersections in front of viewpoint
        // choose the closer one
        found = 1;
        t = glm::min(t1, t2);
    }

    if (found) {
        intersection_pos = eye + screen_ray*t;
        normal = glm::normalize(intersection_pos - center);
    }
    Intersection intersection = Intersection(found, intersection_pos, normal);
    intersection.hit_object_idx = scene_idx;
    return intersection;
}


Triangle::Triangle(
        vec3 vert1, vec3 vert2, vec3 vert3): 
    vert1(vert1), vert2(vert2), vert3(vert3)
{}

Intersection Triangle::intersect(vec3 eye, vec3 screen_ray) {

    return Intersection(0, vec3(1.0), vec3(1.0));
}


Scene::Scene() {
    object_arr = new GeomObject*[128];
    light_arr = new Light*[128];
}
