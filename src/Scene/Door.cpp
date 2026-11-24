#include "Scene/Door.h"

#include "Interfaces/IInteractable.h"
#include "Utilities/Utils.h"

#include <iostream>

Door::Door(Model& modelRef, Model& hingeModelRef)
	: SceneNode(), doorHinge(hingeModelRef), doorObject(modelRef)
{
	doorHinge.AddNodeName("door hinge");
	doorHinge.GetLocalTransform().scaleVector = glm::vec3(0.2f);
	doorHinge.UseTexture(false);
	doorHinge.SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	doorObject.AddNodeName("door object");
	doorObject.SetCollider(Collider{ColliderShape::Box, 0.0f, glm::vec3{1.0f}});
    doorObject.GetLocalTransform().scaleVector = glm::vec3(1.0f, 10.0f, 5.0f);
	doorObject.GetLocalTransform().positionVector.z -= 5.0f;
    doorObject.UseTexture(false);
	doorObject.SetColor(RGBAtoVec4(97, 65, 54, 255));

	doorHinge.SetParent(this);
	doorObject.SetParent(&doorHinge);

	interactionSphere = InteractionSphere{3.0f, glm::vec3{0.0f}};
}

RenderObject& Door::GetDoorHinge()
{
	return doorHinge;
}

GameObject& Door::GetDoorObject()
{
	return doorObject;
}

void Door::SetLocked(bool val)
{
	isLocked = val;
}

bool Door::IsLocked() const
{
	return isLocked;
}

void Door::SetOpen(bool val)
{
	isOpen = val;
}

bool Door::IsOpen() const
{
	return isOpen;
}

void Door::Interact()
{
	if (!isLocked)
	{
		if (!isOpen)
		{
			Open();
		}
		else
		{
			Close();
		}
	}
}

void Door::SetInteractionSphere(InteractionSphere val)
{
	interactionSphere = val;
}

InteractionSphere Door::GetWorldInteractionSphere() const
{
	InteractionSphere worldSphere = interactionSphere;

    const glm::mat4 worldMatrix = GetWorldMatrix();
    worldSphere.center = glm::vec3(worldMatrix * glm::vec4(interactionSphere.center, 1.0f));

    return worldSphere;
}

void Door::Update(float deltaTime)
{
	if (!isAnimating)
		return;

	elapsedTime += deltaTime;

	if (glm::abs(currAngle - targetAngle) > 0.1f)
	{
		currAngle += rotationSpeed * deltaTime;
		doorHinge.GetLocalTransform().SetRotationEuler(glm::vec3
			{
				doorHinge.GetLocalTransform().GetRotationEuler().x,
				currAngle,
				doorHinge.GetLocalTransform().GetRotationEuler().z

			});
	}
	else 
	{
		SetOpen(!isOpen);
		isAnimating = false;
		std::cout << "toggled open, is now: " << IsOpen() << std::endl;
	}
}

void Door::Open()
{
	// Cannot open door if door is already open
	if (isAnimating || isLocked || isOpen)
		return;

	startAngle = currAngle;
	targetAngle = 90.0f;
	rotationSpeed = 50.0f;
	elapsedTime = 0.0f;
	isAnimating = true;
}

void Door::Close()
{
	// Cannot close door if door is already closed
	if (isAnimating || !isOpen)
		return;

    startAngle = currAngle;
    targetAngle = 0.0f;
	rotationSpeed = -50.0f;
    elapsedTime = 0.0f;
    isAnimating = true;
}