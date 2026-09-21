#pragma once

class IShadowCreater
{
public:
	virtual ~IShadowCreater() = default;

	virtual void CreateShadow(VECTOR* owner_pos, bool* owner_is_active, const float& size) = 0;
};