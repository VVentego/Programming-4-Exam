#include "ColliderComponent.h"
#include "TextureComponent.h"
#include <iostream>

void dae::ColliderComponent::FixedUpdate(const double)
{
}

dae::ColliderComponent::ColliderComponent(GameObject* pOwner) :
	Component::Component(pOwner)
{
	const TextureComponent* textureComponent = pOwner->GetComponent<TextureComponent>();
	if (textureComponent != nullptr)
	{
		m_SizeOfCollider = textureComponent->GetSize();
	}

	else std::cerr << "No texture to inherit size from! Collider set to default of 0!" << std::endl;
}

dae::ColliderComponent::ColliderComponent(GameObject* pOwner, const float width, const float height) : 
	Component::Component(pOwner), m_SizeOfCollider{ width, height }
{
}
