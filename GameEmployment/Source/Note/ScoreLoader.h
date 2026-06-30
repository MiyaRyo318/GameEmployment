#pragma once

#include <vector>
#include <string>
#include "Note.h"

struct ScoreData
{
    float HitTime;
    NoteType Type;
};

class ScoreLoader
{
public:

    bool Load(const std::string& fileName);

    const std::vector<ScoreData>& GetScore() const;

private:

    std::vector<ScoreData> m_Score;
};