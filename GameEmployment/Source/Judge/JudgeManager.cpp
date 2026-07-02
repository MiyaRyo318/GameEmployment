#include "JudgeManager.h"
#include <cmath>

JudgeType JudgeManager::Judge(
    float noteTime,
    float currentTime)
{
    float diff = fabs(noteTime - currentTime);

    if (diff <= 0.05f)
    {
        return PERFECT;
    }

    if (diff <= 0.10f)
    {
        return GREAT;
    }

    if (diff <= 0.15f)
    {
        return GOOD;
    }

    return MISS;
}