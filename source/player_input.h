#pragma once
#include<vector>
#include<memory>
#include"input_base.h"

class PC;
class Pad;

class PlayerInput : public InputBase
{
public:

	PlayerInput();

	~PlayerInput() override;

	void Init() override;

	void Update() override;

	const bool IsDash() const override;

	const bool IsPunch() const override;

	const bool IsAvoid()const override;
	
	const bool IsNormalSkill() const override;

	const bool IsStrongSkill() const override;

	const VECTOR GetMoveDir() const override;

	const VECTOR GetCameraDir() const override;

	const VECTOR GetCameraVelocity() const override;

private:

	std::vector<std::shared_ptr<IInput>> inputs_;

	const VECTOR MoveDirPC(std::shared_ptr<PC> pc) const;

	const VECTOR MoveDirPad(std::shared_ptr<Pad> pad) const;

	const VECTOR CameraMoveDirPC(std::shared_ptr<PC> pc) const;

	const VECTOR CameraMoveDirPad(std::shared_ptr<Pad> pad) const;

	const VECTOR CameraMoveVelPC(std::shared_ptr<PC> pc) const;

	const VECTOR CameraMoveVelPad(std::shared_ptr<Pad> pad) const;
};