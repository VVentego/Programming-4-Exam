#pragma once
#include <memory>
#include "Transform.h"
#include <unordered_map>
#include <any>

namespace dae
{
	class Texture2D;
	class Component;

	class GameObject final
	{
	public:
		void Update(const double deltaTime);
		void FixedUpdate(const double fixedTimeStep);
		void Render() const;
		void Start();

		void SetPosition(float x, float y);
		glm::vec3 GetPosition() const { return m_transform.GetPosition(); };

		void AddComponent(const std::string& componentName, std::shared_ptr<dae::Component> ComponentPtr);
		void DestroyComponent(const std::string& componentName);
		void RemoveComponent();
		std::shared_ptr<Component> GetComponent(const std::string& componentName);



		template <typename T>
		std::shared_ptr<T> GetComponent()
		{
			auto it = std::find_if(m_pComponents.begin(), m_pComponents.end(), [](const auto& component) {
				return std::dynamic_pointer_cast<T>(component.second) != nullptr;
				});
			if (it != m_pComponents.end()) {
				return std::dynamic_pointer_cast<T>(it->second);
			}
			else {
				return nullptr;
			}
		}

		bool ComponentExists(const std::string& componentName) const;
		template <typename T> 
		bool ComponentExists() const
		{
			auto it = std::find_if(m_pComponents.begin(), m_pComponents.end(), [](const auto& component) {
				return std::dynamic_pointer_cast<T>(component.second) != nullptr;
				});
			if (it != m_pComponents.end()) return true;
			else return false;
		}

		void Destroy();
		void SetParent(GameObject* pParentObject, const bool worldPositionStays = true);
		GameObject* GetParent() { return m_pParent; }
		int GetChildCount() const { return static_cast<int>(m_pChildren.size()); }
		GameObject* GetChildAt(const int index);
		void RemoveChild(GameObject* pChildObject);
		void AddChild(GameObject* pChildObject, const bool worldPositionStays = true);

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		bool m_IsDestroyed{};
	private:
		void AddChildToVector(GameObject* pChildObject) { m_pChildren.emplace_back(pChildObject); }

		Transform m_transform{};
		glm::vec3 m_LocalPosition{};

		std::unordered_map<std::string, std::shared_ptr<Component>> m_pComponents;
		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*> m_pChildren;
		bool m_NeedsUpdate{ false };
	};
}
