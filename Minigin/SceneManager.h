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

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
	};
}
#endif