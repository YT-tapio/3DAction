#include<vector>
#include<memory>
#include"DxLib.h"
#include"shadow_circle_controller.h"
#include"shadow_circle.h"

ShadowCircleController::ShadowCircleController()
{

}

ShadowCircleController::~ShadowCircleController()
{
	shadows_.clear();
}

void ShadowCircleController::Init()
{
	
}

void ShadowCircleController::Update()
{
	for (auto& shadow : shadows_)
	{
		shadow->Update();
	}
}

const void ShadowCircleController::Draw() const
{
	for (const auto& shadow : shadows_)
	{
		shadow->Draw();
	}
}

void ShadowCircleController::CreateShadow(VECTOR* owner_pos, const float& size)
{
	shadows_.emplace_back(std::make_shared<ShadowCircle>(owner_pos, size));
}