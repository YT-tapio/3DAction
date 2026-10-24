#pragma once

class AnimatorBase;
class Time;

class TitlePlayerController
{
public:

	TitlePlayerController();

	~TitlePlayerController();

	void Init();

	void Update();

	void Draw();

	void Debug();

	const VECTOR GetPos() const;

	const VECTOR GetHeadPos() const;

private:

	void Move();

	void Setting();

private:

	const float kWalkSpeed = 0.1f;
	const float kHeadVertical = 10.f;	// ì™ÇÃçÇÇ≥Ç…çáÇÌÇπÇÈ

	std::shared_ptr<AnimatorBase> animator_;
	std::shared_ptr<Time> time_;

	VECTOR pos_;
	VECTOR scale_;
	VECTOR rotation_;

	VECTOR head_pos_;

	int model_handle_;

};