#pragma once

class VariableTimer;

class Shake
{
public:

	Shake();

	~Shake();

	void Init();

	void Update();

	void Active(const float& power, const float& time);

	const VECTOR GetShakeVel() const;

private:

	std::shared_ptr<VariableTimer> timer_;
	
	VECTOR shake_vel_;

	float power_;

	bool is_active_;

};