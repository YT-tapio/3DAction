#pragma once

class Object3D;

class AttackRange : public Object3D
{
public:

	AttackRange();

	~AttackRange() override;

	void Init() override;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="scale"></param>
	void Init(const VECTOR& pos, const VECTOR& scale);

	void Update() override;

	void Draw() override;

	void Debug() override;

private:

	void LoadFile();

private:

	VECTOR target_scale_;

};