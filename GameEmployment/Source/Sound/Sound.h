#pragma once

class Sound
{
public:

    Sound();
    ~Sound();

    // “Ç‚İ‚İ
    bool Init();

    // ‰ğ•ú
    void End();

    // BGMÄ¶
    void PlayBGM();

    // BGM’â~
    void StopBGM();

private:

    int m_BGMHandle;
};