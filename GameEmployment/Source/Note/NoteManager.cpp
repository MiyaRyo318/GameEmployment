#include "NoteManager.h"

#include <algorithm>

NoteManager::NoteManager()
{

}

NoteManager::~NoteManager()
{

}

void NoteManager::Init()
{
    m_Notes.clear();

    constexpr float NOTE_Y = 500.0f;

    if (!m_ScoreLoader.Load("Data/Score/test.txt"))
    {
        return;
    }

    const auto& score = m_ScoreLoader.GetScore();

    for (const auto& note : score)
    {
        AddNote(
            note.HitTime,
            note.Type,
            NOTE_Y);
    }
}

void NoteManager::Update(float currentTime)
{
    for (auto& note : m_Notes)
    {
        note.Update(currentTime);
    }

    m_Notes.erase(
        std::remove_if(
            m_Notes.begin(),
            m_Notes.end(),
            [](const Note& note)
            {
                return note.IsDead() || note.IsJudge();
            }),
        m_Notes.end());
}

void NoteManager::Draw()
{
    

    // ノーツ
    for (auto& note : m_Notes)
    {
        note.Draw();
    }

    // デバッグ
    DrawFormatString(
        20,
        20,
        GetColor(255, 255, 255),
        "Note Count : %d",
        (int)m_Notes.size());
}

void NoteManager::AddNote(
    float hitTime,
    NoteType type,
    float y)
{
    Note note;

    note.Create(
        hitTime,
        type,
        y,
        -1);

    m_Notes.push_back(note);
}

void NoteManager::Clear()
{
    m_Notes.clear();
}

Note* NoteManager::GetFirstNote()
{
    if (m_Notes.empty())
    {
        return nullptr;
    }

    return &m_Notes.front();
}

Note* NoteManager::GetJudgeNote(NoteType type)
{
    for (auto& note : m_Notes)
    {
        if (note.IsJudge())
        {
            continue;
        }

        if (note.IsDelete())
        {
            continue;
        }

        if (note.GetType() == type)
        {
            return &note;
        }
    }

    return nullptr;
}