#pragma once

class SE
{
public:
    SE();
    ~SE();

    bool Init();
    void End();

    // Œˆ’è‰¹
    void PlayDecision();

    // Perfect
    void PlayPerfect();

    // Miss
    void PlayMiss();

    // ƒhƒ“
    void PlayDon();

    // ƒJƒb
    void PlayKa();

private:
    int m_DecisionSE;
    int m_PerfectSE;
    int m_MissSE;

    // ’Ç‰Á
    int m_DonSE;
    int m_KaSE;
};