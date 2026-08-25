#pragma once

class Object3D;

class AttackRange : public Object3D
{
public:

	AttackRange();

	virtual ~AttackRange() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	void Debug() override;

protected:

	std::function<float()> leading_up_ratio_;

	VECTOR target_scale_;

	// UŒ‚‚ª‚Å‚é‚Ü‚Å‚ÌƒT[ƒNƒ‹
	int leading_up_attack_handle_;

	VECTOR leading_up_pos_;
	VECTOR leading_up_rot_;
	VECTOR leading_up_scale_;

private:

	

};