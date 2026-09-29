#pragma once

class TitleScene
{
public:

    void Init();

    void Update();

    void Draw();

    void End();

    bool IsStart() const;

    bool IsExitGame() const;

private:

    enum class MenuState
    {
        MENU,
        OPERATION
    };

    enum class MenuSelect
    {
        GAME_START,
        OPERATION,
        EXIT_GAME
    };

    bool m_IsStart = false;
    bool m_IsExitGame = false;

    int m_TitleImage = -1;

    MenuState m_MenuState = MenuState::MENU;

    MenuSelect m_MenuSelect = MenuSelect::GAME_START;

    bool m_IsUpKey = false;
    bool m_IsDownKey = false;
    bool m_IsSpaceKey = false;
    bool m_IsEscKey = false;
};