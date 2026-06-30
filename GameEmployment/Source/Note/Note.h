#pragma once

#include "DxLib.h"

enum NoteType
{
    DON,
    KA
};

class Note
{
public:

    Note();

    void Create(
        float hitTime,
        NoteType type,
        float y,
        int image);

    void Update(float currentTime);

    void Draw();

    void SetJudge(bool judge);

    bool IsJudge() const;

    bool IsDead() const;

    float GetHitTime() const;

    NoteType GetType() const;

private:

    float m_HitTime;

    float m_X;
    float m_Y;

    float m_Speed;

    NoteType m_Type;

    bool m_IsJudge;

    int m_Image;
};