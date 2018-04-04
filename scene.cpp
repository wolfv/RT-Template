#include "scene.h"
#include <random>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

Scene::Scene( void )
{}

Scene::~Scene( void )
{}

bool Scene::intersect( const Ray &ray,
                       IntersectionRecord &intersection_record ) const
{
    bool intersection_result = false;
    IntersectionRecord tmp_intersection_record;
    std::size_t num_primitives = primitives_.size();

    // Loops over the list of primitives, testing the intersection of each primitive against the given ray 
    for ( std::size_t primitive_id = 0; primitive_id < num_primitives; primitive_id++ )
        if ( primitives_[primitive_id]->intersect( ray, tmp_intersection_record ) )
            if ( ( tmp_intersection_record.t_ < intersection_record.t_ ) && ( tmp_intersection_record.t_ > 0.0 ) )
            {
                intersection_record = tmp_intersection_record;
                intersection_result = true; // the ray intersects a primitive!
            }

    return intersection_result;
}

void Scene::load(const std::string& filename) 
{
#if 1
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    tinyobj::LoadObj(&attrib, &shapes, nullptr, nullptr, filename.c_str());
    for (auto &&s : shapes) {
        size_t index_offset = 0;
        for (int fv : s.mesh.num_face_vertices) {
            glm::vec3 vertices[3];
            for (size_t v = 0; v < (size_t)fv; ++v) {
                 tinyobj::index_t idx = s.mesh.indices[index_offset + v];

                 tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
                 tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
                 tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
                 vertices[v] = glm::vec3{vx, vy, vz};

            }
            primitives_.push_back(
                Primitive::PrimitiveUniquePtr(
                    new Triangle(vertices[0], vertices[1], vertices[2], glm::vec3(1.f, 1.f, 1.f))
                )
            );
            
            index_offset += fv;
        }
    }

#else
    std::random_device rd;
    std::default_random_engine e(rd());
    std::uniform_real_distribution<float> d(0.f, 1.f);

    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.0f,  0.0f }, 0.2f, glm::vec3{d(e), d(e), d(e)} } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.0f, -1.0f }, 0.2f, glm::vec3{d(e), d(e), d(e)} } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f,-0.5f, -2.0f }, 0.2f, glm::vec3{d(e), d(e), d(e)} } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.5f, -3.0f }, 0.2f, glm::vec3{d(e), d(e), d(e)} } ) );
#endif
}
