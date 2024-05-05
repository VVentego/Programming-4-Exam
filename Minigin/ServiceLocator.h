#ifndef SERVICELOCATOR
#define SERVICELOCATOR
#include "SoundSystem.h"
#include "InputSystem.h"
#include <memory>

class ServiceLocator final
{
public:
	~ServiceLocator() = default;
	ServiceLocator(const ServiceLocator& other) = delete;
	ServiceLocator(ServiceLocator&& other) = delete;
	ServiceLocator& operator=(const ServiceLocator& other) = delete;
	ServiceLocator& operator=(ServiceLocator&& other) = delete;

	static dae::SoundSystem& GetSoundManager() { return *_sm_instance; }
	static dae::InputSystem& GetInputManager() { return *_im_instance; }

	static void RegisterSoundManager(std::unique_ptr<dae::SoundSystem> pSoundManager) 
	{ 
		if (pSoundManager == NULL)
		{
			_sm_instance = std::make_unique<dae::NullSoundSystem>();
		}

		else if (_sm_instance != nullptr)
		{
			_sm_instance->Destroy();
			_sm_instance.reset();
		}
		_sm_instance = std::move(pSoundManager);
	}
	static void RegisterInputManager(std::unique_ptr<dae::InputSystem> pInputManager) 
	{
		if (pInputManager == NULL)
		{
			_im_instance = std::make_unique<dae::NullInputSystem>();
		}

		if (_im_instance != nullptr)
		{
			_im_instance.reset();
		}
		_im_instance = std::move(pInputManager); 
	}
private:
	ServiceLocator() = default;
	static std::unique_ptr<dae::SoundSystem> _sm_instance;
	static std::unique_ptr<dae::InputSystem> _im_instance;
};
#endif // SERVICELOCATOR