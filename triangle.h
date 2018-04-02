#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <glm/glm.hpp>
#include "primitive.h"
#include "intersection_record.h"
#include "ray.h"

struct Triangle : public Primitive
{
    Triangle() = default;
    Triangle(const Triangle &) = default;
    Triangle(Triangle &&) = default;
    Triangle(
        const glm::vec3 &a_,
        const glm::vec3 &b_,
        const glm::vec3 &c_);
    
    bool intersect(const Ray &ray, IntersectionRecord &ir) const;
    
    glm::vec3 a, b, c;
};

#endif
