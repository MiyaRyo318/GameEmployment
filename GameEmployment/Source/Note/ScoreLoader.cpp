#include "ScoreLoader.h"

#include <fstream>

bool ScoreLoader::Load(const std::string& fileName)
{
    m_Score.clear();

    std::ifstream fin(fileName);

    if (!fin.is_open())
    {
        return false;
    }

    float time;

    std::string type;

    while (fin >> time >> type)
    {
        ScoreData data;

        data.HitTime = time;

        if (type == "DON")
        {
            data.Type = DON;
        }
        else if (type == "KA")
        {
            data.Type = KA;
        }
        else if (type == "ORANGE")
        {
            data.Type = ORANGE;
        }
        else if (type == "GREEN")
        {
            data.Type = GREEN;
        }
        else
        {
            continue;
        }

        m_Score.push_back(data);
    }

    fin.close();

    return true;
}

const std::vector<ScoreData>& ScoreLoader::GetScore() const
{
    return m_Score;
}