#ifndef SERVICELOCATOR
#define SERVICELOCATOR
#include "SoundSystem.h"
//#include "InputManager.h"
//#include "ResourceManager.h"
#include "Singleton.h"

class ServiceLocator final : public dae::Singleton<ServiceLocator>
{
public:
	static ServiceLocator& GetInstance()
	{
			static ServiceLocator instance;
			return instance;
	}
	~ServiceLocator() = default;
	ServiceLocator(const ServiceLocator& other) = delete;
	ServiceLocator(ServiceLocator&& other) = delete;
	ServiceLocator& operator=(const ServiceLocator& other) = delete;
	ServiceLocator& operator=(ServiceLocator&& other) = delete;

	SoundSystem& GetSoundManager() { return *_sm_instance; }
	//static dae::ResourceManager& GetResourceManager() { return *_rm_instance; }
	//static dae::InputManager& GetInputManager() { return *_im_instance; }

	void RegisterSoundManager(std::unique_ptr<SoundSystem> pSoundManager) { _sm_instance = std::move(pSoundManager); }
	//static void RegisterResourceManager(std::unique_ptr<dae::ResourceManager> pResourceManager) { _rm_instance = std::move(pResourceManager); }
	//static void RegisterInputManager(std::unique_ptr<dae::InputManager> pInputManager) { _im_instance = std::move(pInputManager); }
private:
	ServiceLocator() = default;
	std::unique_ptr<SoundSystem> _sm_instance;
	//std::unique_ptr<dae::ResourceManager> _rm_instance;
	//std::unique_ptr<dae::InputManager> _im_instance;
};
#endif // SERVICELOCATOR