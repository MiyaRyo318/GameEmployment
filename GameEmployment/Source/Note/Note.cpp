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

        // 連打時間に応じて横幅を決める
        float length = m_Duration * m_Speed;

        // 高さと角の丸み
        int halfHeight = 22;
        int radius = 22;

        int left = (int)m_X;
        int right = left + (int)length;
        int top = (int)m_Y - halfHeight;
        int bottom = (int)m_Y + halfHeight;

        // 横長の本体
        DrawBox(left + radius, top,right - radius, bottom,color, TRUE);

        // 左右の丸い端
        DrawCircle(left + radius, (int)m_Y,radius, color, TRUE);

        DrawCircle(right - radius, (int)m_Y,radius, color, TRUE);

        // 白い縁取り
        DrawBox(left + radius, top,right - radius, bottom,GetColor(255, 255, 255), FALSE);

        DrawCircle(left + radius, (int)m_Y,radius, GetColor(255, 255, 255), FALSE);

        DrawCircle(right - radius, (int)m_Y,radius, GetColor(255, 255, 255), FALSE);

        return;
    }

    // 通常ノーツは従来どおり丸く描画
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

    DrawCircle((int)m_X, (int)m_Y, 28,GetColor(255, 255, 255), TRUE);

    DrawCircle((int)m_X, (int)m_Y, 22, color, TRUE);
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