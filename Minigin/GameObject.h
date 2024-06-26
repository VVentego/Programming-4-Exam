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
	class Scene;
	class ColliderComponent;

	class GameObject final
	{
		friend class Component;
	public:
		void Update(const double deltaTime);
		void FixedUpdate(const double fixedTimeStep);
		void Render() const;
		void SetLocalPosition(const float x, const float y);
		void SetLocalPosition(const glm::vec2& localPosition);
		void SetPositionDirty();
		void Start();

		void SetWorldPosition(const float x, const float y);
		void SetWorldPosition(const glm::vec2& worldPosition);
		const glm::vec2 GetLocalPosition() const;
		const glm::vec2 GetWorldPosition() const;
		void CollisionEvent(GameObject* other);

		void AddComponent(std::unique_ptr<dae::Component> ComponentPtr);
		void AddCollider(Scene& scene);
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
		ColliderComponent* GetCollider() const { return m_pCollider.get(); }
		const Transform* GetTransform() const { return &m_Transform; }
		void SnapToGrid();

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
		std::shared_ptr<ColliderComponent> m_pCollider;
	};
}

enum class Facing
{
	right,
	down,
	left,
	up
};
#endif

