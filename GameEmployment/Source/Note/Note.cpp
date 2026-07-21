#include "Note.h"

constexpr float JUDGE_LINE_X = 200.0f;

Note::Note()
{
    m_HitTime = 0.0f;

    m_X = 0.0f;
    m_Y = 0.0f;

    m_Speed = 400.0f;

    m_Type = DON;

    m_IsJudge = false;
    m_IsDelete = false;

    m_Image = -1;
}

void Note::Create(
    float hitTime,
    NoteType type,
    float y,
    int image)
{
    m_HitTime = hitTime;

    m_Type = type;

    m_Y = y;

    m_Image = image;
}

void Note::Update(float currentTime)
{
    float remain = m_HitTime - currentTime;

    m_X = JUDGE_LINE_X + remain * m_Speed;

    // GOOD判定より遅れたら削除
    if (currentTime > m_HitTime + 0.20f)
    {
        m_IsDelete = true;
    }
}

void Note::Draw()
{
    int color;

    if (m_Type == DON)
    {
        // ドン（赤）
        color = GetColor(255, 0, 0);
    }
    else
    {
        // カッ（青）
        color = GetColor(0, 128, 255);
    }

    // 外側の白い縁
    DrawCircle(
        (int)m_X,
        (int)m_Y,
        28,
        GetColor(255, 255, 255),
        TRUE);

    // 中身
    DrawCircle(
        (int)m_X,
        (int)m_Y,
        22,
        color,
        TRUE);
}

void Note::SetJudge(bool judge)
{
    m_IsJudge = judge;
}

bool Note::IsJudge() const
{
    return m_IsJudge;
}

bool Note::IsDead() const
{
    return m_IsDelete;
}

float Note::GetHitTime() const
{
    return m_HitTime;
}

NoteType Note::GetType() const
{
    return m_Type;
}

void Note::SetDelete(bool flag)
{
    m_IsDelete = flag;
}

bool Note::IsDelete() const
{
    return m_IsDelete;
}

float Note::GetX() const
{
    return m_X;
}