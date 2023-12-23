#pragma once 

#include <glm/glm.hpp>


struct sCamera {
    glm::vec3       camera_center = { 0.0f, 0.0f, 0.0f };

    float           focal_length  = 1.0f;

    glm::vec2       view_port_size = {};
    glm::uvec2      view_port_resolution = {};
    // Inter pixel distance
    glm::vec3       pixel_delta_u = {};
    glm::vec3       pixel_delta_v = {};

    glm::vec3       pixel_00_position = {};


    void init(const glm::vec3 &cam_center, 
              const glm::uvec2 &viewp_resolution, 
              const glm::vec2 &viewp_size) {
        focal_length = 1.0f; // TODO
        camera_center = cam_center;
        view_port_resolution = viewp_resolution;
        view_port_size = viewp_size;

        const glm::vec3 vp_world_size_axis_x = glm::vec3(view_port_size.x, 0.0f, 0.0f);
        const glm::vec3 vp_world_size_axis_y = glm::vec3(0.0f, -view_port_size.y, 0.0f); // Why the minus??

        pixel_delta_u = vp_world_size_axis_x / (float) view_port_resolution.x;
        pixel_delta_v = vp_world_size_axis_y / (float) view_port_resolution.y; 

        const glm::vec3 vp_upper_left_corner = camera_center - glm::vec3(0.0f, 0.0f, focal_length) - 0.5f * vp_world_size_axis_x - 0.5f * vp_world_size_axis_y;

        pixel_00_position = vp_upper_left_corner + 0.5f * (pixel_delta_u + pixel_delta_v);
    }

    inline glm::vec3 get_ray_dir(const uint32_t pixel_u, const uint32_t pixel_v) {
        // Pixel center coordinate - camera center = ray_dir
        return (pixel_00_position + ((float) pixel_u * pixel_delta_u) + ((float) pixel_v * pixel_delta_v)) - camera_center; 
    }
};