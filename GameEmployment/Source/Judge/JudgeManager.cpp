#include "JudgeManager.h"
#include <cmath>

JudgeType JudgeManager::Judge(float noteTime,float currentTime)
{
    float diff = fabs(noteTime - currentTime);

    // Å}0.04ïb
    if (diff <= 0.04f)
    {
        return PERFECT;
    }

    // Å}0.08ïb
    if (diff <= 0.08f)
    {
        return GREAT;
    }

    // Å}0.12ïb
    if (diff <= 0.12f)
    {
        return GOOD;
    }

    return NONE;
}