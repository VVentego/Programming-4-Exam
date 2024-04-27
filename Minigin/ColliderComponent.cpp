#include "ColliderComponent.h"
#include "TextureComponent.h"
#include "SpriteAnimatorComponent.h"
#include <iostream>
#include "Scene.h"

dae::ColliderComponent::ColliderComponent(GameObject* pOwner, Scene& scene) :
	Component::Component(pOwner)
{
	const TextureComponent* textureComponent = pOwner->GetComponent<TextureComponent>();
	const SpriteAnimatorComponent* spriteComponent = pOwner->GetComponent<SpriteAnimatorComponent>();
	scene.AddCollider(this);
	if (textureComponent != nullptr)
	{
		m_SizeOfCollider = textureComponent->GetSize();
	}

	if (spriteComponent != nullptr)
	{
		m_SizeOfCollider = spriteComponent->GetSize();
	}

	else std::cerr << "No texture to inherit size from! Collider set to default of 0!" << std::endl;
}

dae::ColliderComponent::ColliderComponent(GameObject* pOwner, Scene& scene, const float width, const float height) : 
	Component::Component(pOwner), m_SizeOfCollider{ width, height }
{
	scene.AddCollider(this);
}

void dae::ColliderComponent::CollisionCallback(GameObject* other)
{
	m_pOwner->CollisionEvent(other);
}

dae::GameObject* dae::ColliderComponent::GetOwner()
{
	return m_pOwner;
}

const glm::vec2 dae::ColliderComponent::GetPosition()
{
	return m_pOwner->GetWorldPosition();
}
