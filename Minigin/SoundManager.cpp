#include "SoundManager.h"

void dae::SoundManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;
	m_SoundSystemImpl->Init();
}

void dae::SoundManager::Play(const sound_id id, const int volume)
{
	m_SoundSystemImpl->Play(id, volume);
}

void dae::SoundManager::Destroy()
{
	m_SoundSystemImpl->Destroy();
}

void dae::SoundManager::AddTrack(const std::string& fileName, const sound_id id)
{
	const auto fullPath = m_dataPath + fileName;
	m_SoundSystemImpl->AddTrack(fullPath, id);
}

dae::SoundManager::SoundManager() :
	SoundSystem()
{
	m_SoundSystemImpl = std::make_unique<SoundSystemImpl>();
}
