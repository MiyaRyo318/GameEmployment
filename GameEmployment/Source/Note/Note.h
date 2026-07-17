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

    void SetDelete(bool flag);

    bool IsJudge() const;

    bool IsDead() const;

    bool IsDelete() const;

    float GetHitTime() const;

    float GetX() const;

    NoteType GetType() const;

private:

    float m_HitTime;

    float m_X;
    float m_Y;

    float m_Speed;

    NoteType m_Type;

    bool m_IsJudge;

    bool m_IsDelete;

    int m_Image;
};