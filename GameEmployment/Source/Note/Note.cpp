#include "Note.h"

constexpr float JUDGE_LINE_X = 200.0f;

Note::Note()
{
    m_HitTime = 0.0f;

    m_X = 0.0f;
    m_Y = 0.0f;

    m_Speed = 500.0f;

    m_Type = DON;

    m_IsJudge = false;
    m_IsDelete = false;

    m_Image = -1;

    m_Duration = 0.0f;
    m_RendanHits = 0;
}

void Note::Create(float hitTime, NoteType type, float y,int image, float duration)
{
    m_HitTime = hitTime;
    m_Type = type;
    m_Y = y;
    m_Image = image;
    m_Duration = duration;
    m_RendanHits = 0;

    m_X = JUDGE_LINE_X + m_HitTime * m_Speed;

    m_IsJudge = false;
    m_IsDelete = false;
}

void Note::Update(float currentTime)
{
    float remain = m_HitTime - currentTime;

    // 連打ノーツも通常ノーツと同じ速度で左へ流す
    m_X = JUDGE_LINE_X + remain * m_Speed;

    // ノーツの終了時刻
    float endTime = m_HitTime + m_Duration;

    if (m_Type == RENDAN)
    {
        // 連打の終端が判定ラインを通過してから削除
        if (currentTime > endTime + 0.20f)
        {
            m_IsDelete = true;
        }
    }
    else
    {
        if (currentTime > m_HitTime + 0.20f)
        {
            m_IsDelete = true;
        }
    }
}


void Note::Draw()
{
    // 連打ノーツは横長に描画
    if (m_Type == RENDAN)
    {
        int color = GetColor(255, 220, 0);

        float length = m_Duration * m_Speed;

        int halfHeight = 22;
        int radius = 22;

        int left = (int)m_X;
        int right = left + (int)length;
        int top = (int)m_Y - halfHeight;
        int bottom = (int)m_Y + halfHeight;

        DrawBox(left + radius, top, right - radius, bottom, color, TRUE);
        DrawCircle(left + radius, (int)m_Y, radius, color, TRUE);
        DrawCircle(right - radius, (int)m_Y, radius, color, TRUE);

        DrawBox(left + radius, top, right - radius, bottom,GetColor(255, 255, 255), FALSE);

        DrawCircle(left + radius, (int)m_Y, radius,GetColor(255, 255, 255), FALSE);

        DrawCircle(right - radius, (int)m_Y, radius,GetColor(255, 255, 255), FALSE);

        return;
    }

    // 通常ノーツの色
    int color = GetColor(255, 255, 255);

    if (m_Type == DON)
    {
        color = GetColor(255, 0, 0);
    }
    else if (m_Type == KA)
    {
        color = GetColor(0, 128, 255);
    }
    else if (m_Type == ORANGE)
    {
        color = GetColor(255, 128, 0);
    }
    else if (m_Type == GREEN)
    {
        color = GetColor(0, 200, 0);
    }
    else if (m_Type == BRANCH)
    {
        // 分岐ノーツは紫色
        color = GetColor(180, 0, 255);
    }

    DrawCircle((int)m_X, (int)m_Y, 28,GetColor(255, 255, 255), TRUE);

    DrawCircle((int)m_X, (int)m_Y, 22, color, TRUE);

    // 分岐ノーツにはBの文字を表示
    if (m_Type == BRANCH)
    {
        DrawString((int)m_X - 7, (int)m_Y - 8,"B", GetColor(255, 255, 255));
    }
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

void Note::AddRendanHit()
{
    m_RendanHits++;
}

int Note::GetRendanHits() const
{
    return m_RendanHits;
}

float Note::GetDuration() const
{
    return m_Duration;
}