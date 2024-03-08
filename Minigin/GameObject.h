#ifndef GAMEOBJECT 
#define GAMEOBJECT
#include <memory>
#include "Transform.h"
#include <unordered_map>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
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
		void SetLocalPosition(const float x, const float y, const float z);
		void SetLocalPosition(const glm::vec3& localPosition);
		void SetPositionDirty();
		void Start();

		void SetWorldPosition(const float x, const float y, const float z);
		void SetWorldPosition(const glm::vec3& worldPosition);
		const glm::vec3 GetWorldPosition() const;

		void AddComponent(const std::string& componentName, std::unique_ptr<dae::Component> ComponentPtr);
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
		GameObject* GetChildAt(const size_t index);
		bool IsChild(GameObject* pParent);

		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		bool m_IsDestroyed{};
	private:

		Transform m_Transform{};

		std::unordered_map<std::string, std::shared_ptr<Component>> m_pComponents;
		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*> m_pChildren;
		bool m_TransformNeedsUpdate{ false };

		void RemoveChild(GameObject* pChildObject);
		void AddChild(GameObject* pChildObject);
		void RecalculateTransform();
	};
}
#endif