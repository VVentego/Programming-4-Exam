#ifndef SCENE
#define SCENE
#include "SceneManager.h"
#include "GameObject.h"
#include "ColliderComponent.h"

namespace dae
{
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();
		void RemoveAllPersistentObjects();
		void Update(const double deltaTime);
		void FixedUpdate(const double fixedTimeStep);
		void Render() const;
		void Destroy();
		void AddCollider(std::shared_ptr<ColliderComponent> pCollider);
		void UpdateCollisions() const;
		void AddPersistentObject(std::unique_ptr<GameObject> object);
		void RemovePersistentObject(std::unique_ptr<GameObject> object);
		std::vector<std::unique_ptr<GameObject>>& PassPersistentObjects();

		std::vector<std::unique_ptr<GameObject>>* GetPersistentObjects();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		const std::string m_name;
	private: 
		explicit Scene(const std::string& name);

		std::vector<std::unique_ptr<GameObject>> m_objects{};
		mutable std::vector<std::weak_ptr<ColliderComponent>> m_pColliders{};
		static unsigned int m_idCounter; 
		std::vector<std::unique_ptr<GameObject>> m_PersistentObjects{};
	};

}
#endif // !SCENE