#pragma once
#include"object_3D.h"
#include"vector_assistant.h"

class Stage : public Object3D
{
public:

	Stage();

	~Stage() override;

	void Init() override;

	void Update() override;

	void Draw() override;

protected:



private:

	const char* kPath			= "a";
	const VECTOR kPos		= VectorAssistant::VGetZero();

};