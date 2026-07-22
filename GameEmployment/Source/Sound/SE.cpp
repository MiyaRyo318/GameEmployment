#include "SE.h"
#include "DxLib.h"

SE::SE()
{
    m_DecisionSE = -1;
    m_PerfectSE = -1;
    m_MissSE = -1;

    m_DonSE = -1;
    m_KaSE = -1;
}

SE::~SE()
{

}

bool SE::Init()
{
    m_DecisionSE = LoadSoundMem("Data/Sound/Decision.wav");

    m_PerfectSE = LoadSoundMem("Data/Sound/Perfect.wav");

    m_MissSE = LoadSoundMem("Data/Sound/Miss.wav");

    m_DonSE = LoadSoundMem("Data/Sound/Don.wav");
    m_KaSE = LoadSoundMem("Data/Sound/Ka.wav");

    ChangeVolumeSoundMem(150, m_DonSE);
    ChangeVolumeSoundMem(150, m_KaSE);

    return true;
}

void SE::End()
{
    DeleteSoundMem(m_DecisionSE);

    DeleteSoundMem(m_PerfectSE);

    DeleteSoundMem(m_MissSE);

    DeleteSoundMem(m_DonSE);
    DeleteSoundMem(m_KaSE);
}

void SE::PlayDecision()
{
    PlaySoundMem(
        m_DecisionSE,
        DX_PLAYTYPE_BACK);
}

void SE::PlayPerfect()
{
    PlaySoundMem(
        m_PerfectSE,
        DX_PLAYTYPE_BACK);
}

void SE::PlayMiss()
{
    PlaySoundMem(
        m_MissSE,
        DX_PLAYTYPE_BACK);
}

void SE::PlayDon()
{
    PlaySoundMem(
        m_DonSE,
        DX_PLAYTYPE_BACK);
}

void SE::PlayKa()
{
    PlaySoundMem(
        m_KaSE,
        DX_PLAYTYPE_BACK);
}