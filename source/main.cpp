#include<iostream>
#include"DxLib.h"
#include"application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    
    std::shared_ptr<Application> app = std::make_shared<Application>();

    app->Update();
    
    return 0;        // ソフトの終了
}