#ifndef INTERACTION_RENDERER_H
#define INTERACTION_RENDERER_H

#include "Core/Scene.h"
#include "Interfaces/IInteractable.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"

class InteractionRenderer
{
private:
    bool showInteractionSpheres{};
    GLuint sphereVAO{};
    GLuint sphereVBO{};
    GLuint sphereEBO{};
    int sphereIndexCount{};
    int sphereSegments{16};
    int sphereRings{12};

public:
    InteractionRenderer();

    void SetShowInteractionSpheres(bool newVal);
    bool ShowInteractionSpheres() const;

    void InitializeInteractionSpheres();

    void DrawInteractionSphere(const IInteractable& interactable, Shader& shader);
    void DrawInteractionSpheres(Scene& scene, Shader& shader);
};

#endif