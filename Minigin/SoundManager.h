#ifndef SOUNDMANAGER
#define SOUNDMANAGER
#include <memory>
#include <map>
#include <mutex>
#include "Singleton.h"
#include "SoundSystem.h"

struct Mix_Chunk;
struct _Mix_Music;

namespace dae
{
    class SoundManager : public SoundSystem
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

		virtual void Init(const std::string& dataPath) override;
		virtual void Play(const sound_id id, const int volume) override;
		virtual void PlayMusic() override;
		virtual void StopMusic() override;
		virtual void Destroy() override;
		virtual void AddTrack(const std::string& fileName, sound_id id);
		virtual void AddMusic(const std::string& fileName) override;
	protected:
		std::string m_dataPath{};

		class SoundSystemImpl;
		std::unique_ptr<SoundSystemImpl> m_SoundSystemImpl;
    };
#endif // !SOUNDMANAGER

	class SoundManagerDebug final : public SoundManager
	{
	public:
		SoundManagerDebug() = default;
		~SoundManagerDebug() = default;
		SoundManagerDebug(const SoundManagerDebug& other) = delete;
		SoundManagerDebug(SoundManagerDebug&& other) noexcept
		{
			m_dataPath = other.m_dataPath;
			m_SoundSystemImpl = std::move(other.m_SoundSystemImpl);
		}
		SoundManagerDebug& operator=(const SoundManagerDebug& other) = delete;
		SoundManagerDebug& operator=(SoundManagerDebug&& other) noexcept
		{
			m_dataPath = other.m_dataPath;
			m_SoundSystemImpl = std::move(other.m_SoundSystemImpl);
			return *this;
		}

		void Init(const std::string& dataPath) override;
		void Play(const sound_id id, const int volume) override;
		void AddTrack(const std::string& fileName, sound_id id) override;
		void AddMusic(const std::string& fileName) override;
		virtual void PlayMusic() override;
		virtual void StopMusic() override;
		void ToggleMute() override;
	};

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
		void LoadTrack(const std::string& fileName, sound_id id);
		void AddTrack(const std::string& fileName, sound_id id);
		void AddMusic(const std::string& fileName);
		void PlayMusic();
		void StopMusic();
		void Destroy();

	private:
		static const int MAX_PENDING{ 16 };
		PlayMessage m_Pending[MAX_PENDING]{};
		int head_{};
		int tail_{};
;		std::mutex mutex;
		std::map<sound_id, Mix_Chunk*> m_AudioTracks;
		_Mix_Music* m_Music{};
		std::map<sound_id, std::string> m_TracksToLoad;
		std::jthread m_SoundThread;
		std::jthread m_LoadingThread;
		std::condition_variable cv{};
		std::condition_variable cv1{};
		bool m_Running{ true };
		void Update();
		void UpdateLoadedTracks();
	};
#endif // !SOUNDSYSTEMIMPL
}
