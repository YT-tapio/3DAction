#pragma once
#include<vector>
#include"input_base.h"

class Player;

class AIInput : public InputBase
{
public:

	AIInput();

	~AIInput();

	void Init() override;

	void Update() override;

	const bool IsDash() const override;

	const bool IsPunch() const override;

	const bool IsAvoid() const override;

	const bool IsJump() const override;

	const bool IsNormalSkill() const override;

	const bool IsStrongSkill() const override;

	const VECTOR GetMoveDir() const override;

	const VECTOR GetCameraDir() const override;

private:

	// オーナーを取得する
	std::weak_ptr<Player> owner_;

};