#pragma once
#include<memory>
#include"behavior_base.h"

class PlaySound3D : public BehaviorBase
{
public:

	PlaySound3D(std::weak_ptr<ObjectBase> owner,VECTOR* pos,const std::string& name);

	~PlaySound3D() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

private:

	VECTOR* pos_;
	std::string name_;

};