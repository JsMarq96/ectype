#pragma once

#include <glm/glm.hpp>

namespace Intersection {

    inline bool ray_sphere(const glm::vec3 &sphere_center, 
                           const float sphere_radius,
                           const glm::vec3 &ray_origin,
                           const glm::vec3 &ray_dir) {
        // Compute the number of roots of the equation via the quadratic formula 
        const glm::vec3 origin_center = ray_origin - sphere_center;
        const float a = glm::dot(ray_dir, ray_dir); // ray_dir ^ 2
        const float b = 2.0f * glm::dot(origin_center, ray_dir); // 2.0 * facingness of ray_dir and and center to center vector
        const float c = glm::dot(origin_center, origin_center) - sphere_radius * sphere_radius;
        const float roots = b * b - 4.0f * a * c; 
        return roots >= 0.0f;
    }

};