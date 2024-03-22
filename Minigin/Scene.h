#ifndef SCENE
#define SCENE

#include "SceneManager.h"
#include "GameObject.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();
		void AddObserver(std::shared_ptr<PlayerObserver> observer);
		void RemoveObserver(std::shared_ptr<PlayerObserver> observer);
		void Update(const double deltaTime);
		void FixedUpdate(const double fixedTimeStep);
		void Render() const;
		void Destroy();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector<std::unique_ptr<GameObject>> m_objects{};
		std::vector<std::shared_ptr<PlayerObserver>> m_observers{};

		static unsigned int m_idCounter; 
	};

}
#endif // !SCENE