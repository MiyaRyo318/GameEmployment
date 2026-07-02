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

    m_DonImage = LoadGraph("Data/Image/Don.png");
    m_KaImage = LoadGraph("Data/Image/Ka.png");

    constexpr float NOTE_Y = 500.0f;

    AddNote(1.0f, DON, NOTE_Y);
    AddNote(2.0f, KA, NOTE_Y);
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

    if (type == DON)
    {
        note.Create(
            hitTime,
            type,
            y,
            m_DonImage);
    }
    else
    {
        note.Create(
            hitTime,
            type,
            y,
            m_KaImage);
    }

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