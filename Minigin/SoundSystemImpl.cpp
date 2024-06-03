#include "SoundManager.h"
#include <SDL_mixer.h>
#include <cassert>

dae::SoundManager::SoundSystemImpl::~SoundSystemImpl()
{
}

void dae::SoundManager::SoundSystemImpl::Play(const sound_id id, const int volume)
{
    std::unique_lock<std::mutex> lock(mutex);
    assert((tail_ + 1) % MAX_PENDING != head_);

    for (int i = head_; i != tail_; i = (i + 1) % MAX_PENDING)
    {
        if (m_Pending[i].id == id)
        {
            m_Pending[i].volume = std::max(volume, m_Pending[i].volume);
            cv.notify_one();
            return;
        }
    }

    m_Pending[tail_].id = id;
    m_Pending[tail_].volume = volume;
    tail_ = (tail_ + 1) % MAX_PENDING;
    cv.notify_one();
    //auto trackIt = m_AudioTracks.find(id);
    //Mix_Chunk* track = trackIt->second;
    //Mix_VolumeChunk(track, volume);

    //int result = Mix_PlayChannel(-1, track, 0);
    //
    //assert(result != -1);
}

bool dae::SoundManager::SoundSystemImpl::Init()
{
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        return false;
    }

    head_ = 0;
    tail_ = 0;

    m_SoundThread = std::jthread(&SoundSystemImpl::Update, this);
    m_LoadingThread = std::jthread(&SoundSystemImpl::UpdateLoadedTracks, this);

    for (int i{}; i < MAX_PENDING; ++i)
    {
        m_Pending[i] = PlayMessage{ 0,0 };
    }

    return true;
}

void dae::SoundManager::SoundSystemImpl::LoadTrack(const std::string& fileName, sound_id id)
{
    Mix_Chunk* track = Mix_LoadWAV(fileName.c_str()); 

    assert(track != nullptr);

    m_AudioTracks.insert(std::pair<sound_id, Mix_Chunk*>(id, track));
}

void dae::SoundManager::SoundSystemImpl::AddTrack(const std::string& fileName, sound_id id)
{
    m_TracksToLoad.insert(std::pair<sound_id, std::string>(id, fileName));
    cv1.notify_one();
}

void dae::SoundManager::SoundSystemImpl::AddMusic(const std::string& fileName)
{
    m_Music = Mix_LoadMUS(fileName.c_str());
    assert(m_Music != nullptr);
}

void dae::SoundManager::SoundSystemImpl::PlayMusic()
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(m_Music, -1);
    }

    else
    {
        Mix_ResumeMusic();
    }
}

void dae::SoundManager::SoundSystemImpl::StopMusic()
{
    Mix_PauseMusic();
}

void dae::SoundManager::SoundSystemImpl::Destroy()
{
    for (auto& track : m_AudioTracks)
    {
        Mix_FreeChunk(track.second);
    }

    if (m_Music != nullptr)
    {
        Mix_FreeMusic(m_Music);
    }

    m_Running = false;
    cv.notify_one();
    cv1.notify_one();

    if (m_SoundThread.joinable())
    {
        m_SoundThread.join();
    }

    if (m_LoadingThread.joinable())
    {
        m_LoadingThread.join();
    }
    Mix_CloseAudio();
}

void dae::SoundManager::SoundSystemImpl::Update()
{
    while (m_Running)
    {
        std::unique_lock<std::mutex> lock(mutex);

        cv.wait(lock, [this] { return !(head_ == tail_) || !m_Running; });

        auto trackIt = m_AudioTracks.find(m_Pending[head_].id);
        if (trackIt != m_AudioTracks.end())
        {
            Mix_Chunk* track = trackIt->second;
            Mix_VolumeChunk(track, m_Pending[head_].volume);
            Mix_PlayChannel(-1, track, 0);
        }

        head_ = (head_ + 1) % MAX_PENDING;
    }
}

void dae::SoundManager::SoundSystemImpl::UpdateLoadedTracks()
{
    while (m_Running)
    {
        std::unique_lock<std::mutex> lock(mutex);

        cv1.wait(lock, [this] { return !m_TracksToLoad.empty() || !m_Running; });

        if (!m_TracksToLoad.empty())
        {
            for (auto& track : m_TracksToLoad)
            {
                LoadTrack(track.second, track.first);
            }
            m_TracksToLoad.clear();
        }
    }
}