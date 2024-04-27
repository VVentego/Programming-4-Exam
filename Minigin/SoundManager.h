#ifndef SOUNDMANAGER
#define SOUNDMANAGER
#include <memory>
#include <map>
#include <mutex>
#include "Singleton.h"
#include "SoundSystem.h"

struct Mix_Chunk;

namespace dae
{
    class SoundManager final : public SoundSystem
    {
	public:
		SoundManager();
		virtual ~SoundManager() = default;
		SoundManager(const SoundManager& other) = delete;
		SoundManager(SoundManager&& other) noexcept
		{
			m_dataPath = other.m_dataPath;
			m_SoundSystemImpl = std::move(other.m_SoundSystemImpl);
		}
		virtual SoundManager& operator=(const SoundManager& other) = delete;
		virtual SoundManager& operator=(SoundManager&& other) noexcept
		{ 
			m_dataPath = other.m_dataPath;
			m_SoundSystemImpl = std::move(other.m_SoundSystemImpl);
			return *this;
		}

		void Init(const std::string& dataPath) override;
		void Play(const sound_id id, const int volume) override;
		void Destroy() override;
		void AddTrack(const std::string& fileName, sound_id id);
	private:
		std::string m_dataPath{};

		class SoundSystemImpl;
		std::unique_ptr<SoundSystemImpl> m_SoundSystemImpl;
    };
#endif // !SOUNDMANAGER

#ifndef SOUNDSYSTEMIMPL
#define SOUNDSYSTEMIMPL
	class SoundManager::SoundSystemImpl final
	{
		struct PlayMessage
		{
			sound_id id;
			int volume;
		};
	public:
		SoundSystemImpl() = default;
		virtual ~SoundSystemImpl();
		SoundSystemImpl(const SoundSystemImpl& other) = delete;
		SoundSystemImpl(SoundSystemImpl&& other) = delete;
		SoundSystemImpl& operator=(const SoundSystemImpl& other) = delete;
		SoundSystemImpl& operator=(SoundSystemImpl&& other) = delete;
		void Play(const sound_id id, const int volume);
		bool Init();
		void AddTrack(const std::string& fileName, sound_id id);
		void Destroy();

	private:
		static const int MAX_PENDING{ 16 };
		PlayMessage m_Pending[MAX_PENDING]{};
		int head_{};
		int tail_{};
;		std::mutex mutex;
		std::map<sound_id, Mix_Chunk*> m_AudioTracks;
		std::jthread m_SoundThread;
		std::condition_variable cv{};
		bool m_Running{ true };
		void Update();
	};
#endif // !SOUNDSYSTEMIMPL
}
