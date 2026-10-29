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
    float duration;

    while (fin >> time >> type)
    {
        ScoreData data;

        data.HitTime = time;
        data.Duration = 0.0f;

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
        else if (type == "RENDAN")
        {
            data.Type = RENDAN;

            if (!(fin >> data.Duration))
            {
                data.Duration = 2.0f;
            }
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