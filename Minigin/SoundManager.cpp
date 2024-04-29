#include "SoundManager.h"
#include <iostream>

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

void dae::SoundManagerDebug::Init(const std::string& dataPath)
{
	SoundManager::Init(dataPath);
	std::cout << "SoundManager initialised successfully in debug mode." << std::endl;
}

void dae::SoundManagerDebug::Play(const sound_id id, const int volume)
{
	SoundManager::Play(id, volume);
	std::cout << "Playing sound of ID: " << std::to_string(id) << " at volume: " << std::to_string(volume) << std::endl;
}

void dae::SoundManagerDebug::AddTrack(const std::string& fileName, sound_id id)
{
	SoundManager::AddTrack(fileName, id);
	std::cout << "SoundManager added track of name: " << fileName << " and ID " << std::to_string(id) << std::endl;
}

