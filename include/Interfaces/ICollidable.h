#ifndef ICOLLIDABLE_H
#define ICOLLIDABLE_H

#include <glm/gtc/type_ptr.hpp>

enum class ColliderShape
{
    Box,
    Sphere
};

struct Collider
{
    ColliderShape colliderShape{ColliderShape::Box};
    float radius{0.0f};
    glm::vec3 halfSize{0.0f};
    glm::vec3 center{0.0f};
};

class ICollidable
{
public:
    virtual Collider GetWorldCollider() const = 0;
};

#endif