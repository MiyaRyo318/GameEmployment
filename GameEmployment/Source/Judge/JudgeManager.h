#pragma once

enum JudgeType
{
    NONE,
    PERFECT,
    GREAT,
    GOOD,
    MISS
};

class JudgeManager
{
public:

    JudgeType Judge(float noteTime, float currentTime);

};