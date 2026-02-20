#pragma once

class Brain
{
public:

	Brain();

	~Brain();

	void Init();

	void Update();

private:

	VECTOR vel_;
	VECTOR target_vel_;

};