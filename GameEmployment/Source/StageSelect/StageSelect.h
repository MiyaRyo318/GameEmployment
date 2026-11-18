#pragma once
#include "DxLib.h"

class StageSelect
{
public:

    StageSelect();

    void Init();

    void Update();

    void Draw();

    bool IsSelected() const;

    int GetSelectedStage() const;

private:

    int m_SelectedStage;

    bool m_IsSelected;
};