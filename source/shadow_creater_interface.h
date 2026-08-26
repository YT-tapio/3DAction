#pragma once

class IShadowCreater
{
public:
	virtual ~IShadowCreater() = default;

	virtual void CreateShadow(VECTOR* owner_pos, const float& size);
};