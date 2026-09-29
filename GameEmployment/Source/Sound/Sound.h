#pragma once

class Sound
{
public:

    Sound();
    ~Sound();

    bool Init();

    void End();

    // BGMçƒê∂
    void PlayBGM();

    // BGMí‚é~
    void StopBGM();

    // BGMÇ™èIóπÇµÇΩÇ©
    bool IsBGMFinished() const;

private:

    int m_BGMHandle;
};