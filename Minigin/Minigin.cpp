#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"
#include "InputManager.h"
#include "Renderer.h"
#include "SceneManager.h"
#include <chrono>
#include <thread>
#include <math.h>
#include "SoundManager.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"

SDL_Window* g_window{};
using namespace std::chrono;

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const char* dataPath) : 
	m_RefreshRate{ GetMonitorRefreshRate() }
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		gWindowWidth,
		gWindowHeight,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);

	ServiceLocator::RegisterInputManager(std::make_unique<InputManager>());

#if _DEBUG
	ServiceLocator::RegisterSoundManager(std::make_unique<SoundManagerDebug>());
#else
	ServiceLocator::RegisterSoundManager(std::make_unique<SoundManager>());
#endif
	ServiceLocator::GetSoundManager().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	
	ServiceLocator::GetSoundManager().Destroy();

	g_window = nullptr;

	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = ServiceLocator::GetInputManager();

	bool doContinue = true;
	auto lastTime = high_resolution_clock::now();
	double lag{ 0.f };
	constexpr double fixedTimeStep{ 1 / 60.0 };
	const milliseconds timeBetweenFrames{ milliseconds(1000) / m_RefreshRate};

	while (doContinue)
	{
		const auto currentTime = high_resolution_clock::now();
		double deltaTime = duration<double>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag += deltaTime;

		input.UpdateInput(deltaTime);
		doContinue = !input.HasQuit();
		while (lag >= fixedTimeStep)
		{
			sceneManager.FixedUpdate(fixedTimeStep);
			lag -= fixedTimeStep;
		};
		sceneManager.Update(deltaTime);
		renderer.Render();
		sceneManager.DestroyObjects();

		const auto sleepTime{ currentTime + timeBetweenFrames - high_resolution_clock::now()};

		std::this_thread::sleep_for(sleepTime);
	}
}

const int dae::Minigin::GetMonitorRefreshRate() {
	DISPLAY_DEVICE dd{};
	dd.cb = sizeof(dd);
	EnumDisplayDevices(nullptr, 0, &dd, 0);

	DEVMODE dm{};
	dm.dmSize = sizeof(dm);
	EnumDisplaySettings(dd.DeviceName, ENUM_CURRENT_SETTINGS, &dm);

	return dm.dmDisplayFrequency;
}
