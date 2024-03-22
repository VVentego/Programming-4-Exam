#ifndef GAMEOBJECT 
#define GAMEOBJECT
#include <memory>
#include "Transform.h"
#include <vector>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

namespace dae
{
	class Texture2D;

	class GameObject final
	{
		friend class Component;
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
		const glm::vec3 GetLocalPosition() const;
		const glm::vec3 GetWorldPosition() const;

		void AddComponent(std::unique_ptr<dae::Component> ComponentPtr);
		template <typename T>
		void DestroyComponent()
		{
			if (ComponentExists<T>() == true)
			{
				T* componentToDelete = GetComponent<T>();
				componentToDelete->Destroy();
			}
		}
		void RemoveComponent();

		template <typename T>
		T* GetComponent()
		{
			auto it = std::find_if(m_pComponents.begin(), m_pComponents.end(), [](const auto& component) {
				return dynamic_cast<T*>(component.get()) != nullptr;
				});
			if (it != m_pComponents.end()) {
				return dynamic_cast<T*>(it->get());
			}
			else {
				return nullptr;
			}
		}

		template <typename T> 
		bool ComponentExists() const
		{
			auto it = std::find_if(m_pComponents.begin(), m_pComponents.end(), [](const auto& component) {
				return dynamic_cast<T*>(component.get()) != nullptr;
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

		std::vector<std::unique_ptr<Component>> m_pComponents;
		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*> m_pChildren;
		bool m_TransformNeedsUpdate{ false };

		void RemoveChild(GameObject* pChildObject);
		void AddChild(GameObject* pChildObject);
		void RecalculateTransform();
	};
}
#endif