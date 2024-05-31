#ifndef SCENEMANAGER
#define SCENEMANAGER

#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update(const double deltaTime);
		void FixedUpdate(const double fixedTimeStep);
		void Render();
		void DestroyObjects();
		void TransferPersistentObjects(Scene& first, Scene& second);
		std::shared_ptr<Scene> GetCurrentScene();
		std::shared_ptr<Scene> GetScene(const std::string& name);

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
	};
}
#endif