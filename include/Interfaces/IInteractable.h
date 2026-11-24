#ifndef IINTERACTABLE_H
#define IINTERACTABLE_H

#include <glm/gtc/type_ptr.hpp>

struct InteractionSphere
{
    float radius{2.0f};
    glm::vec3 center{0.0f};
};

class IInteractable
{
public:
    virtual ~IInteractable() = default;
    virtual void Interact() = 0;
    virtual InteractionSphere GetWorldInteractionSphere() const = 0;
};

#endif