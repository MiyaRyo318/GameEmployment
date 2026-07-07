#pragma once

#include <vector>
#include "Note.h"
#include "ScoreLoader.h"

class NoteManager
{
public:

    NoteManager();

    ~NoteManager();

    void Init();

    void Update(float currentTime);

    void Draw();

    void AddNote(float hitTime, NoteType type, float y);

    void Clear();

    Note* GetFirstNote();

    Note* GetJudgeNote(NoteType type);

private:

    std::vector<Note> m_Notes;

    ScoreLoader m_ScoreLoader;

    int m_DonImage;

    int m_KaImage;
};