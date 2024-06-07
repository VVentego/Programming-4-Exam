#include "SoundManager.h"
#include <iostream>

void dae::SoundManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;
	m_SoundSystemImpl->Init();
}

void dae::SoundManager::Play(const sound_id id, const int volume)
{
	if (!m_Muted)
	{
		m_SoundSystemImpl->Play(id, volume);
	}
}

void dae::SoundManager::PlayMusic()
{
	if (!m_Muted)
	{
		m_SoundSystemImpl->PlayMusic();
	}
}

void dae::SoundManager::StopMusic()
{
	m_SoundSystemImpl->StopMusic();
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

void dae::SoundManager::AddMusic(const std::string& fileName)
{
	m_SoundSystemImpl->AddMusic(fileName);
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
	if (m_Muted) return;

	SoundManager::Play(id, volume);
	std::cout << "Playing sound of ID: " << std::to_string(id) << " at volume: " << std::to_string(volume) << std::endl;
}

void dae::SoundManagerDebug::AddTrack(const std::string& fileName, sound_id id)
{
	SoundManager::AddTrack(fileName, id);
	std::cout << "SoundManager added track of name: " << fileName << " and ID " << std::to_string(id) << std::endl;
}

void dae::SoundManagerDebug::AddMusic(const std::string& fileName)
{
	SoundManager::AddMusic(fileName);
	std::cout << "SoundManager added music track of name: " << fileName << std::endl;
}

void dae::SoundManagerDebug::PlayMusic()
{
	SoundManager::PlayMusic();
}

void dae::SoundManagerDebug::StopMusic()
{
	SoundManager::StopMusic();
}

void dae::SoundManagerDebug::ToggleMute()
{
	SoundSystem::ToggleMute();
	if (m_Muted == true)
	{
		std::cout << "Sound muted!" << std::endl;
	}

	else
	{
		std::cout << "Sound unmuted!" << std::endl;
	}
}