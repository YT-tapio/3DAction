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

	void SetInvincible(bool flag);

	void Teleport(const VECTOR& pos);

	const VECTOR GetAttackTargetPos() const;

	const bool GetIsInvincible() const;
	
	virtual const bool GetOnGround() const;

	const VECTOR GetVelocity() const;

	std::shared_ptr<AnimatorBase> GetAnimator();

protected:

	VECTOR dir_;
	VECTOR vel_;

	bool is_invincible_;

	bool is_ground_;

	// todo:アニメーションをつけてください
	std::shared_ptr<AnimatorBase> animator_;

private:

};