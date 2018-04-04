#include "triangle.h"
#include <cmath>

Triangle::Triangle(const glm::vec3 &a_, const glm::vec3 &b_, const glm::vec3 &c_, const glm::vec3 &color)
    : Primitive::Primitive{color}, a{a_}, b{b_}, c{c_}
{}

bool Triangle::intersect(const Ray &ray, IntersectionRecord &ir) const
{
    using glm::vec3;

    vec3 ab = b - a;
    vec3 ac = c - a;
    vec3 pvec = glm::cross(ray.direction_, ac);
    float det = glm::dot(ab, pvec);

    if (std::fabs(det) < 1e-6f) {
        return false;
    }
    float inv_det = 1.f / det;

    vec3 tvec = ray.origin_ - a;
    float u = glm::dot(tvec, pvec) * inv_det;
    if (u < 0.f || u > 1.f) {
    return false;
    }

    vec3 qvec = glm::cross(tvec, ab);
    float v = glm::dot(ray.direction_, qvec) * inv_det;
    if (v < 0.f || u+v > 1.f) {
        return false;
    }

    ir.t_ = glm::dot(ac, qvec) * inv_det;
    ir.color = &color;
    ir.position_ = ray.origin_ + ir.t_ * ray.direction_;
    ir.normal_ = glm::normalize(glm::cross(ab, ac));

    return true;
}
