#include "JudgeManager.h"
#include <cmath>

JudgeType JudgeManager::Judge(
    float noteTime,
    float currentTime)
{
    float diff = fabs(noteTime - currentTime);

    if (diff <= 0.20f)
    {
        return PERFECT;
    }

    if (diff <= 0.40f)
    {
        return GREAT;
    }

    if (diff <= 0.60f)
    {
        return GOOD;
    }

    return MISS;
}