#pragma once
#include"object_3D.h"

class CharacterBase : public Object3D
{
public:

	CharacterBase(const char* path, const VECTOR& pos, const VECTOR& rot, const VECTOR& scale);

	virtual ~CharacterBase() override;

	virtual void Init() override;

	virtual void Update() override;

	virtual void Draw() override;

protected:

	// todo:アニメーションのをつけてください

private:

};