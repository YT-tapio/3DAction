#pragma once
#include"object_Base.h"

class Object3D : public ObjectBase
{
public:

	Object3D(const char* id);

	virtual ~Object3D() override;

	virtual void Init() override;

	virtual void Update() override;

	virtual void Draw() override;

	virtual void Debug() override;

protected:

	MATRIX mat_;
	VECTOR scale_;

	std::string path_;

	int handle_;

	void LoadModel();

	void Setting();

private:

	void LoadFile();

};