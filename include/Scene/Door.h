#ifndef DOOR_H
#define DOOR_H

#include "Interfaces/IAnimatable.h"
#include "Interfaces/IInteractable.h"
#include "Scene/GameObject.h"
#include "Scene/RenderObject.h"
#include "Scene/SceneNode.h"

class Door : public SceneNode, public IInteractable, public IAnimatable
{
private:
	RenderObject doorHinge;
    GameObject doorObject;

	InteractionSphere interactionSphere;

	bool isLocked{false};
	bool isOpen{false};
	bool isAnimating{false};

	float currAngle{0.0f};
	float startAngle{0.0f};
	float targetAngle{90.0f};
	float rotationSpeed{50.0f};

	float animationDuration{10.0f};
	float elapsedTime{0.0f};

public:
	Door(Model& modelRef, Model& hingeModelRef);

	RenderObject& GetDoorHinge();
	GameObject& GetDoorObject();

	void SetLocked(bool val);
	bool IsLocked() const;

	void SetOpen(bool val);
	bool IsOpen() const;

	void SetInteractionSphere(InteractionSphere val);

	void Interact() override;
	InteractionSphere GetWorldInteractionSphere() const override;

	void Update(float deltaTime) override;

	void Open();
	void Close();
};

#endif