#include "Sound.h"
#include "DxLib.h"

Sound::Sound()
{
    m_BGMHandle = -1;
}

Sound::~Sound()
{

}

bool Sound::Init()
{
    m_BGMHandle = LoadSoundMem("Data/Sound/BGM.mp3");

    if (m_BGMHandle == -1)
    {
        return false;
    }

    return true;
}

void Sound::End()
{
    if (m_BGMHandle != -1)
    {
        DeleteSoundMem(m_BGMHandle);
    }
}

void Sound::PlayBGM()
{
    // âπó ê›íËÅi0Å`255Åj
    ChangeVolumeSoundMem(100, m_BGMHandle);

    if (CheckSoundMem(m_BGMHandle) == 0)
    {
        PlaySoundMem(m_BGMHandle,DX_PLAYTYPE_BACK,FALSE);
    }
}

void Sound::StopBGM()
{
    StopSoundMem(m_BGMHandle);
}

bool Sound::IsBGMFinished() const
{
    if (m_BGMHandle == -1)
    {
        return false;
    }

    return CheckSoundMem(m_BGMHandle) == 0;
}