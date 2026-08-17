#pragma once
#include"fade_color_type.h"
#include"condition_timer.h"
#include"variable_timer.h"

class Fade
{
public:

	static Fade& GetInstance()
	{
		static Fade instance;
		return instance;
	}

	void Awake();

	void Update();

	void Draw();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="time"></param>
	/// <param name="type"></param>
	void StartFadeIn(const float& time, FadeColorType type);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="time"></param>
	void StartFadeOut(const float& time);

	const bool IsFinished() const;

private:

	Fade();

	void DrawBox();

private:

	enum class FadeType
	{
		kNone,
		kFadeIn,
		kFadeOut,
	};

	const float kMaxAlphaValue = 255;

	std::shared_ptr<VariableTimer> timer_;

	FadeColorType fade_color_type_;
	FadeType fade_type_;

	float alpha_;
	bool start_;
	bool is_finished_;
};