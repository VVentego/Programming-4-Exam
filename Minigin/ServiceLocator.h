#ifndef SERVICELOCATOR
#define SERVICELOCATOR
#include "SoundSystem.h"
#include "InputSystem.h"
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
	dae::InputSystem& GetInputManager() { return *_im_instance; }

	void RegisterSoundManager(std::unique_ptr<SoundSystem> pSoundManager) 
	{ 
		if (_sm_instance != nullptr)
		{
			_sm_instance->Destroy();
			_sm_instance.reset();
		}
		_sm_instance = std::move(pSoundManager);
	}
	void RegisterInputManager(std::unique_ptr<dae::InputSystem> pInputManager) 
	{
		if (_im_instance != nullptr)
		{
			_im_instance.reset();
		}
		_im_instance = std::move(pInputManager); 
	}
private:
	ServiceLocator() = default;
	std::unique_ptr<SoundSystem> _sm_instance;
	std::unique_ptr<dae::InputSystem> _im_instance;
};
#endif // SERVICELOCATOR