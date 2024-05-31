#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(const double deltaTime)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
		scene->UpdateCollisions();
	}
}

void dae::SceneManager::FixedUpdate(const double fixedTimeStep)
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(fixedTimeStep);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::DestroyObjects()
{
	for (const auto& scene : m_scenes)
	{
		scene->Destroy();
	}
}

void dae::SceneManager::TransferPersistentObjects(Scene& first, Scene& second)
{
	auto& persistentObjects = first.PassPersistentObjects();
	for (auto& object : persistentObjects)
	{
		second.AddPersistentObject(std::move(object));
	}
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetCurrentScene() 
{
	if (m_scenes.empty())
	{
		return nullptr;
	}

	return m_scenes.front(); 
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetScene(const std::string& name)
{
	auto it = std::find_if(m_scenes.begin(), m_scenes.end(), [&name](const std::shared_ptr<Scene> scene)
		{
			return scene->m_name == name;
		});

	if (it != m_scenes.end())
	{
		return *it;
	}

	return nullptr;
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
