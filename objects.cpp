#include "objects.h"


Intersection::Intersection(int found, vec4 position, vec4 normal): 
    found(found), position(position), normal(normal)
{}

GeomObject::GeomObject() {

}

Sphere::Sphere(
        vec4 ambient, vec4 diffuse, vec4 specular, vec4 emission, vec4 center, float radius): 
    ambient(ambient), diffuse(diffuse), specular(specular), 
    emission(emission), center(center), radius(radius)
{}


Intersection Sphere::intersect(vec4 eye, vec4 screen_ray) {
    Intersection intersection(1, vec4(1.0), vec4(1.0));

    int found = 0;
    vec4 intersection_pos(1.0);
    vec4 normal(1.0);
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
        // both intersection behind the eye viewpoint
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
        // two intersection in front of viewpoint
        // choose the closer one
        found = 1;
        t = glm::min(t1, t2);
    }

    if (found) {
        intersection_pos = eye + screen_ray*t1;
        normal = glm::normalize(intersection_pos - center);
    }

    return Intersection(found, intersection_pos, normal);
}


Triangle::Triangle(
        vec4 ambient, vec4 diffuse, vec4 specular, vec4 emission, vec4 center,
        vec4 vert1, vec4 vert2, vec4 vert3): 
    ambient(ambient), diffuse(diffuse), specular(specular), 
    emission(emission), vert1(vert1), vert2(vert2), vert3(vert3)
{}

Intersection Triangle::intersect(vec4 eye, vec4 screen_ray) {

    return Intersection(0, vec4(1.0), vec4(1.0));
}
