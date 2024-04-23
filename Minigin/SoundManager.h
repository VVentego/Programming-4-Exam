#ifndef SOUNDMANAGER
#include "Singleton.h"
#include "SDL_mixer.h"

namespace dae
{
    class SoundManager final :
        public Singleton<SoundManager>
    {
	public:
		static SoundManager& GetInstance() {
			static SoundManager instance;
			return instance;
		}
		virtual ~SoundManager() = default;
		SoundManager(const SoundManager& other) = delete;
		SoundManager(SoundManager&& other) = delete;
		SoundManager& operator=(const SoundManager& other) = delete;
		SoundManager& operator=(SoundManager&& other) = delete;

	private:
		SoundManager();
    };
}
#endif // !SOUNDMANAGER
