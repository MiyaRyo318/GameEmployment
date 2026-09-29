#include "DxLib.h"
#include "Scene/SceneManager.h"

int WINAPI WinMain(
    HINSTANCE,
    HINSTANCE,
    LPSTR,
    int)
{
    ChangeWindowMode(TRUE);

    SetGraphMode(1600, 900, 32);

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    SceneManager scene;

    scene.Init();

    while (ProcessMessage() == 0)
    {
        scene.Update();

        ClearDrawScreen();

        scene.Draw();

        ScreenFlip();
    }

    scene.End();

    DxLib_End();

    return 0;
}