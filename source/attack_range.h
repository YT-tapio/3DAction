#pragma once

class Object3D;

class AttackRange : public Object3D
{
public:

	AttackRange();

	virtual ~AttackRange() override;

	void Init() override;

	void Update() override;

	virtual void Active(const VECTOR& pos, const VECTOR& scale);

	void Draw() override;

	void Debug() override;

protected:

	VECTOR target_scale_;

private:

	

};