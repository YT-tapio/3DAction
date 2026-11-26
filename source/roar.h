#pragma once
#include"behavior_status.h"
#include"behavior_base.h"

class ObjectBase;

class Roar : public BehaviorBase
{
public:

	Roar(std::shared_ptr<ObjectBase> owner,const std::string& anim_name);

	~Roar();

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

private:

	std::string anim_name_;
	bool is_character_;

};