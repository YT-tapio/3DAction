#include"DxLib.h"
#include"sub_screen.h"


SubScreen::SubScreen(int screen_width, int screen_height)
	: screen_width_(screen_width)
	, screen_height_(screen_height)
{
	// スクリーンを用意
	handle_ = MakeScreen(screen_width, screen_height, TRUE);
}

SubScreen::~SubScreen()
{
	DeleteGraph(handle_);
}

void SubScreen::Init()
{

}

void SubScreen::Up()
{
	// スクリーンの起動
	SetDrawScreen(handle_);
	ClearDrawScreen();
}

void SubScreen::Down()
{
	//スクリーンを閉じる
	SetDrawScreen(DX_SCREEN_BACK);
}

const int SubScreen::GetScreenWidth() const
{
	return screen_height_;
}

const int SubScreen::GetScreenHeight() const
{
	return screen_height_;
}

const int SubScreen::GetHandle() const
{
	return handle_;
}

