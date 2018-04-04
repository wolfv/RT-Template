#include "pinhole_camera.h"

PinholeCamera::PinholeCamera(
    const float min_x,
    const float max_x,
    const float min_y,
    const float max_y,
    const float distance_to_screen,
    const glm::ivec2 &resolution,
    const glm::vec3 &position,
    const glm::vec3 &up,
    const glm::vec3 &lookat)
    : Camera::Camera(resolution, position, up, lookat)
    , min_x{min_x}
    , max_x{max_x}
    , min_y{min_y}
    , max_y{max_y}
    , s{distance_to_screen}
{}

Ray
PinholeCamera::getWorldSpaceRay(const glm::vec2 &pixel_coord) const
{
    float width = max_x - min_x;
    float height = max_y - min_y;

    glm::vec3 s_point{
    	(pixel_coord[0] + .5f) / static_cast<float>(resolution_[0]) * width + min_x,
        (pixel_coord[1] + .5f) / static_cast<float>(resolution_[1]) * -height + max_y,
        -s
    };

    return Ray{position_, glm::normalize(onb_.getBasisMatrix() * s_point)};
}
