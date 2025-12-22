#pragma once
#include"object_3D.h"

class CharacterBase : public Object3D
{
public:

	CharacterBase(const char* id);

	virtual ~CharacterBase() override;

	virtual void Init() override;

	virtual void Update() override;

	virtual void Draw() override;

	virtual void Debug() override;

protected:

	// todo:アニメーションをつけてください

private:

};