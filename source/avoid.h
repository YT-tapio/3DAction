#pragma once
#include"behavior_base.h"

class Avoid : public BehaviorBase
{
public:

	Avoid(std::weak_ptr<ObjectBase> owner);

	~Avoid() override;

	void Init() override;

	void Update() override;

	void Debug() override;

private:

	std::string my_anim_name_;

};