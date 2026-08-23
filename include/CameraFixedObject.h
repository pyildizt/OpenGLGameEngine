#ifndef CAMERA_FIXED_OBJECT_H
#define CAMERA_FIXED_OBJECT_H

#include "Camera.h"
#include "RenderObject.h"

class CameraFixedObject : public RenderObject
{
private:
    Camera* camera;

public:
    CameraFixedObject(Model& modelRef);
    CameraFixedObject(Camera& cameraRef, Model& modelRef);

    void SetCamera(Camera& cameraRef);
    Camera& GetCamera() const;

    glm::mat4 GetMatrix();
};

#endif