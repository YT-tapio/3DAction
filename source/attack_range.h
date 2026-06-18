#pragma once

class Object3D;

class AttackRange : public Object3D
{
public:

	AttackRange();

	~AttackRange() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	void Debug() override;

	void SetTransform(const VECTOR& pos, const VECTOR& rot, const VECTOR& scale);

private:

	void LoadFile();

private:

};