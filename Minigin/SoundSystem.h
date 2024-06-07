#pragma once
#include <string>
using sound_id = unsigned short;
namespace dae
{
	class SoundSystem
	{
	public:
		SoundSystem() = default;
		virtual ~SoundSystem() = default;

		virtual void Init(const std::string& dataPath) = 0;
		virtual void Play(const sound_id id, const int volume) = 0;
		virtual void AddTrack(const std::string& fileName, sound_id id) = 0;
		virtual void AddMusic(const std::string& fileName) = 0;
		virtual void Destroy() = 0;
		virtual void PlayMusic() = 0;
		virtual void StopMusic() = 0;
		virtual void ToggleMute()
		{
			if (!m_Muted)
			{
				m_Muted = true;
				StopMusic();
			}
			else
			{
				m_Muted = false;
			}
		}
	protected:
		bool m_Muted{};
	};

	class NullSoundSystem : public SoundSystem
	{
	public:
		NullSoundSystem() = default;
		virtual ~NullSoundSystem() = default;

		void Init(const std::string&) override {};
		void Play(const sound_id, const int) override {};
		void AddTrack(const std::string&, sound_id) override {};
		void AddMusic(const std::string&) override {};
		void Destroy() override {};
		virtual void PlayMusic() override {};
		virtual void StopMusic() override {};
	};
}