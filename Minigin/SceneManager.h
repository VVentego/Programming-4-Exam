#ifndef SCENEMANAGER
#define SCENEMANAGER

#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "LevelState.h"

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
		void RemoveCurrentScene();
		void TransferPersistentObjects(Scene& first, Scene& second);
		std::vector<std::unique_ptr<GameObject>>* GetPersistentObjects();
		Scene* GetCurrentScene();
		Scene* GetScene(const std::string& name);
		void SetLevelState(std::unique_ptr<LevelState> levelState);

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
		std::unique_ptr<LevelState> m_LevelState{};
	};
}
#endif