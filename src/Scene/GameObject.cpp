#include "Scene/GameObject.h"

GameObject::GameObject(Model& modelRef)
    : RenderObject(modelRef)
{

}

void GameObject::SetCollider(const Collider& newCollider)
{
    collider = newCollider;
}

/// <summary>
/// Translate from collider's local bounds to world bounds
/// </summary>
Collider GameObject::GetWorldCollider() const
{
    Collider worldCollider = collider;
    
    const glm::mat4 worldMatrix = GetWorldMatrix();
    worldCollider.center = glm::vec3(worldMatrix * glm::vec4(collider.center, 1.0f));
    worldCollider.halfSize = CalculateAABBHalfSize(glm::mat3{worldMatrix}, collider.halfSize);

    return worldCollider;
}

glm::vec3 GameObject::CalculateAABBHalfSize(const glm::mat3& worldTransform, const glm::vec3& localHalfSize) const
{
    /*
     * Object with hx, hy and hz rotated (a) degrees around the z-axis would now have bounding box:
     * hx' = hx * |cos(a)| + hy * |sin(a)|, hy' = hx * |sin(a)| + hy * |cos(a)|, hz' = hz
     * The idea here is that AABB bounding boxes always have to be paralel to xyx axes,
     * meanwhile objects can be rotated any way. And a rotated object needs a bigger bounding box.
     */

    const glm::vec3 axisX = worldTransform[0];
    const glm::vec3 axisY = worldTransform[1];
    const glm::vec3 axisZ = worldTransform[2];

    glm::vec3 halfSize{};
    halfSize.x = glm::abs(axisX.x) * localHalfSize.x + glm::abs(axisY.x) * localHalfSize.y + glm::abs(axisZ.x) * localHalfSize.z;
    halfSize.y = glm::abs(axisX.y) * localHalfSize.x + glm::abs(axisY.y) * localHalfSize.y + glm::abs(axisZ.y) * localHalfSize.z;
    halfSize.z = glm::abs(axisX.z) * localHalfSize.x + glm::abs(axisY.z) * localHalfSize.y + glm::abs(axisZ.z) * localHalfSize.z;

    return halfSize;
}