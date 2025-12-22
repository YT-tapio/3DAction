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

	void Debug() override;

protected:



private:


	void LoadFile();

};