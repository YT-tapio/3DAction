#include<iostream>
#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"application.h"
#include"scene_manager.h"

Application::Application()
{
    const int kScreenWidth      = 1600;
    const int kScreenHeight     = 900;

    SetGraphMode(kScreenWidth,kScreenHeight, 32);			//ウィンドウのサイズとカラーモードを決める
    ChangeWindowMode(TRUE);				//ウィンドウモードにする

    if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
    {
        return;    // エラーが起きたら直ちに終了
    }

    // DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
  // Effekseerを使用するには必ず設定する。
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    // 引数には画面に表示する最大パーティクル数を設定する。
    if (Effkseer_Init(20000) == -1) { DxLib_End(); }

    // フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
    // Effekseerを使用する場合は必ず設定する。
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // DXライブラリのデバイスロストした時のコールバックを設定する。
    // ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    SetLightEnable(TRUE);


    // Zバッファを有効にする。
    // Effekseerを使用する場合、2DゲームでもZバッファを使用する。
    SetUseZBuffer3D(TRUE);

    // Zバッファへの書き込みを有効にする。
    // Effekseerを使用する場合、2DゲームでもZバッファを使用する。
    SetWriteZBuffer3D(TRUE);

    // 描画先画面を裏画面にする
    SetDrawScreen(DX_SCREEN_BACK);

    SetUseZBufferFlag(TRUE);		// Ｚバッファを使用する
    SetUseBackCulling(TRUE);		// バックカリングを行う

    SetUseSetDrawScreenSettingReset(FALSE);

    scene_manager_ = std::make_shared<SceneManager>();

}


Application::~Application()
{
    Effkseer_End();
	DxLib_End();        // ＤＸライブラリ使用の終了処理
}

void Application::Update()
{

    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
    {
        scene_manager_->Update();
    }
    
}