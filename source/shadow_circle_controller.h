#pragma once
#include"shadow_creater_interface.h"

class ShadowCircle;

class ShadowCircleController : public IShadowCreater
{
public:

	ShadowCircleController();

	~ShadowCircleController() override;

	void Init();

	void Update();

	const void Draw() const;

	void CreateShadow(VECTOR* owner_pos, const float& size) override;

private:

	// 
	std::vector<std::shared_ptr<ShadowCircle>> shadows_;

};