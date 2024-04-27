#pragma once
using sound_id = unsigned short;
class SoundSystem
{
public:
	SoundSystem() = default;
	virtual ~SoundSystem() = default;

	virtual void Init(const std::string& dataPath) = 0;
	virtual void Play(const sound_id id, const int volume) = 0;
	virtual void AddTrack(const std::string& fileName, sound_id id) = 0;
	virtual void Destroy() = 0;
};