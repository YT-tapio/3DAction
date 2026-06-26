#include"DxLib.h"
#include"shadow_map.h"

ShadowMap::ShadowMap()
{
	handle_ = MakeShadowMap(1024, 1024);
	if (handle_ == -1) { printfDx("影：読み込みエラー"); }
	// ライトの方向を設定
	SetLightDirection(VGet(0.5f, -0.5f, 0.5f));
	// ライトの調整
	SetShadowMapLightDirection(handle_, VGet(0.5f, -0.5f, 0.5f));
	SetShadowMapDrawArea(handle_, VGet(-500.0f, -100.0f, -500.0f), VGet(500.0f, 100.0f, 500.0f));
}

ShadowMap::~ShadowMap()
{
	DeleteShadowMap(handle_);
}

void ShadowMap::Init()
{

}

void ShadowMap::UpDrawShadowObject()
{
	SetShadowMapDrawArea(handle_, VGet(-500.0f, -100.0f, -500.0f), VGet(500.0f, 100.0f, 500.0f));
	ShadowMap_DrawSetup(handle_);
}

void ShadowMap::DownDrawShadowObject()
{
	ShadowMap_DrawEnd();
}

void ShadowMap::UpDrawnShadowObject()
{
	SetUseShadowMap(0, handle_);
}

void ShadowMap::DownDrawnShadowObject()
{
	SetUseShadowMap(0, -1);
}
