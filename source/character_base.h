#pragma once
#include"object_3D.h"

class AnimatorBase;

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

	VECTOR dir_;
	VECTOR vel_;

	// todo:アニメーションをつけてください
	std::shared_ptr<AnimatorBase> animator_;

private:

};