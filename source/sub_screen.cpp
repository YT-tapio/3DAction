#include"DxLib.h"
#include"sub_screen.h"


SubScreen::SubScreen(int screen_width, int screen_height)
	: width_(screen_width)
	, height_(screen_height)
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

const int SubScreen::GetWidth() const
{
	return width_;
}

const int SubScreen::GetHeight() const
{
	return height_;
}

const int SubScreen::GetHandle() const
{
	return handle_;
}

const VECTOR SubScreen::GetCenterPos() const
{
	VECTOR center_pos = VGet(static_cast<float>(width_) * 0.5, static_cast<float>(height_) * 0.5, 0.f);
	return center_pos;
}

