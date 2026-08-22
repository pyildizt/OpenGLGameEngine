#ifndef CAMERA_FIXED_OBJECT_H
#define CAMERA_FIXED_OBJECT_H

#include "Camera.h"
#include "Model.h"
#include "Transform.h"

class CameraFixedObject
{
private:
    bool isActive{true};
    Camera* camera;
    Model* model;
    Transform transform;
    
public:
    CameraFixedObject(Model& modelRef);
    CameraFixedObject(Camera& cameraRef, Model& modelRef);

    void SetActive(bool newVal);
    bool IsActive() const;

    void SetCamera(Camera& cameraRef);
    Camera& GetCamera() const;

    Model& GetModel() const;

    Transform& GetTransform();
    glm::mat4 GetMatrix();

    void DrawObject() const;
};

#endif