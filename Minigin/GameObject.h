#pragma once
#include <memory>
#include "Transform.h"
#include <unordered_map>
#include <any>

namespace dae
{
	class Texture2D;
	class Component;
	// todo: this should become final.
	class GameObject final
	{
	public:
		virtual void Update(const double deltaTime);
		virtual void FixedUpdate(const double fixedTimeStep);
		virtual void Render() const;
		virtual void Start();

		//virtual void SetTexture(const std::string& filename);
		virtual void SetPosition(float x, float y);
		glm::vec3 GetPosition() const { m_transform.GetPosition(); };

		virtual void AddComponent(const std::string& componentName, std::shared_ptr<dae::Component> ComponentPtr) final;
		virtual void RemoveComponent(const std::string& componentName) final;
		virtual std::shared_ptr<Component> GetComponent(const std::string& componentName) final;

		virtual bool ComponentExists(const std::string& componentName) const final;

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	protected:
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		//std::shared_ptr<Texture2D> m_texture{};
		std::unordered_map<std::string, std::shared_ptr<Component>> m_pComponents;
	};
}
