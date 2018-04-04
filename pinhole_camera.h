#ifndef PINHOLE_CAMERA_H_
#define PINHOLE_CAMERA_H_

#include "camera.h"
#include "ray.h"

class PinholeCamera : public Camera
{
public:

    PinholeCamera(
        const float min_x,
        const float max_x,
        const float min_y,
        const float max_y,
        const float distance_to_screen,
        const glm::ivec2 &resolution,
        const glm::vec3 &position,
        const glm::vec3 &up,
        const glm::vec3 &lookat);

    Ray getWorldSpaceRay(const glm::vec2 &pixel_coord) const;

    float min_x, max_x, min_y, max_y;

private:
    float s; // distance from center of projection to the screen
};

#endif
