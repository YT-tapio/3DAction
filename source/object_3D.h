#pragma once
#include"object_Base.h"

class Object3D : public ObjectBase
{
public:

	Object3D(const char* path, const VECTOR& pos, const VECTOR& rot, const VECTOR& scale);

	virtual ~Object3D() override;

	virtual void Init() override;

	virtual void Update() override;

	virtual void Draw() override;

protected:

	MATRIX mat_;
	VECTOR scale_;

	int handle_;

	void Setting();

private:


};