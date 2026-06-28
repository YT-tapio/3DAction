#pragma once
#include<memory>
#include"DxLib.h"

class Time;

class ObjectBase
{
public:

	ObjectBase();
	
	virtual ~ObjectBase();
	
	virtual void Init();

	virtual void Update();

	virtual void LateUpdate();

	virtual void Draw();

	virtual void  Debug();

	std::shared_ptr<Time> GetTime();

	const bool GetIsActive() const;

	const VECTOR GetPosition() const;

protected:

	std::shared_ptr<Time> time_;

	VECTOR pos_;
	VECTOR rot_;

	bool is_active_;

private:

	

};