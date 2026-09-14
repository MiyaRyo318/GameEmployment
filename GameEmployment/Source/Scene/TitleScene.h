#pragma once

class TitleScene
{
public:

    void Init();

    void Update();

    void Draw();

    void End();

    bool IsStart() const;

private:

    enum class MenuState
    {
        MENU,
        OPERATION
    };

    enum class MenuSelect
    {
        GAME_START,
        OPERATION
    };

    bool m_IsStart = false;

    int m_TitleImage = -1;

    MenuState m_MenuState = MenuState::MENU;

    MenuSelect m_MenuSelect = MenuSelect::GAME_START;

    // ÉLÅ[ì¸óÕÇÃòAë±îΩâûñhé~
    bool m_IsUpKey = false;
    bool m_IsDownKey = false;
    bool m_IsSpaceKey = false;
    bool m_IsEscKey = false;
};