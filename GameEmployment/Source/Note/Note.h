#pragma once
#include "DxLib.h"

enum NoteType
{
    DON,
    KA,
    ORANGE,
    GREEN,
    RENDAN
};

class Note
{
public:

    Note();

    void Create(float hitTime, NoteType type, float y, int image,float duration = 0.0f);

    void Update(float currentTime);

    void Draw();

    void SetJudge(bool judge);

    void SetDelete(bool flag);

    bool IsJudge() const;

    bool IsDead() const;

    bool IsDelete() const;

    float GetHitTime() const;

    float GetX() const;

    NoteType GetType() const;

    void AddRendanHit();
    int GetRendanHits() const;
    float GetDuration() const;

private:

    float m_HitTime;

    float m_X;
    float m_Y;

    float m_Speed;

    NoteType m_Type;

    bool m_IsJudge;

    bool m_IsDelete;

    int m_Image;

    float m_Duration;
    int m_RendanHits;
};