#include <iostream>

#include "findray.h"
#include "objects.h"
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

    //std::cout << "Created eye coordinate frame: " << std::endl;
    //std::cout << glm::to_string(w) << std::endl << glm::to_string(u) << std::endl 
    //    << glm::to_string(v) << std::endl;

    float alpha = glm::tan(glm::radians(float(fovx))/2) * ((i - float(WIDTH)/2)/(float(WIDTH)/2));
    float beta = glm::tan(glm::radians(float(fovy)/2)) * (((float(HEIGHT)/2) - j)/(float(HEIGHT)/2));
    //std::cout << "alpha: " << alpha << std::endl;
    //std::cout << "beta: " << beta << std::endl;

    vec3 screen_coord = glm::normalize(alpha*u + beta*v - w);
    
    vec3 ray = eye + screen_coord;
    //std::cout << "Computed normalized ray for pixel " << i << ',' << j << ": " << 
    //    glm::to_string(screen_coord) << std::endl;

    return screen_coord;
}


Intersection find_intersection(Scene scene, vec3 eye, vec3 screen_ray) {
    // find the closest intersection by iterating through the
    // scene objects
    
    Intersection found_intersection = Intersection(0, vec3(1.0), vec3(1.0));

    int i;
    for (i = 0; i < scene.used_objects; i++) {
        GeomObject* geom_obj = scene.object_arr[i];
        Intersection intersection = geom_obj->intersect(eye, screen_ray);
        if (intersection.found) {
            if (glm::l2Norm(intersection.position - eye) < glm::l2Norm(found_intersection.position - eye)) {
                // current intersection better (closer) than the previous best
                found_intersection = intersection;
            }
        }
    }

    return found_intersection;
}

vec4 compute_single_light(const vec3 direction, const vec4 lightcolor, const vec3 normal, const vec3 halfvec, const vec4 mydiffuse, const vec4 myspecular, const float myshininess) {

	float nDotL = glm::dot(normal, direction)  ;         
	vec4 lambert = mydiffuse * lightcolor * glm::max(nDotL, 0.0f) ;  

	float nDotH = glm::dot(normal, halfvec) ; 
	vec4 phong = myspecular * lightcolor * glm::pow(glm::max(nDotH, 0.0f), myshininess) ; 

	vec4 retval = lambert + phong ; 
	return retval;            
}  

vec4 find_color(Scene scene, Intersection intersection, vec3 pov) {

    //GeomObject object = intersection->hit_object;

    // iterate through all of the lights to see what the
    // individual contributions to the color to the pixel are
	vec3 eyedirn = glm::normalize(pov - intersection.position); 

    GeomObject* hit_object = scene.object_arr[intersection.hit_object_idx];
    vec4 acc_color = hit_object->ambient + hit_object->emission;

    int i;
    for (i = 0; i < scene.used_lights; i++) {
        Light* light = scene.light_arr[i];
        vec4 light_position = light->position;
        // calculate light directions
        vec3 direction;
        if (light->position.w != 0) {
            // point light
            vec3 position = vec3(light_position) / light_position.w;
            direction = glm::normalize(position - intersection.position);
        } else {
            direction = glm::normalize(vec3(light_position));
        }
        
        vec3 half_vec = glm::normalize(direction + eyedirn); 
        vec4 partial_color = compute_single_light(
            direction, light->color, intersection.normal, half_vec,
            hit_object->diffuse, hit_object->specular, hit_object->shininess) ;

        acc_color += partial_color;

    }

    return acc_color;
}
