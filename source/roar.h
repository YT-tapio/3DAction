#pragma once
#include"behavior_status.h"
#include"behavior_base.h"

class ObjectBase;

class Roar : public BehaviorBase
{
public:

	Roar(std::shared_ptr<ObjectBase> owner);

	~Roar();

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

private:

	bool is_character_;

};