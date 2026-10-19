#include<memory>
#include"DxLib.h"
#include"zoom.h"
#include"condition_timer.h"
#include"variable_timer.h"
#include"lerp.h"

Zoom::Zoom()
	: zoom_in_timer_(std::make_unique<VariableTimer>())
	, zoom_timer_(std::make_unique<VariableTimer>())
	, zoom_out_timer_(std::make_unique<VariableTimer>())
	, state_(ZoomState::kNotActive)
	, current_fov_(0.f)
	, zoom_value_(0.f)
	, is_active_(FALSE)
	, is_zoom_(FALSE)
{

}

Zoom::~Zoom()
{

}

void Zoom::Init()
{
	zoom_in_timer_->Init();
	zoom_timer_->Init();
	zoom_out_timer_->Init();
}

void Zoom::Update()
{	
	switch (state_)
	{
	case ZoomState::kNotActive:
		zoom_value_ = 0.f;
		break;

	case ZoomState::kZoomIn:
		ZoomInUpdate();
		break;

	case ZoomState::kZoom:
		ZoomUpdate();
		break;

	case ZoomState::kZoomOut:
		ZoomOutUpdate();
		break;

	default:

		break;
	}

}

void Zoom::Activate(const float& target_fov, const float& time, const float& active_time)
{
	state_ = ZoomState::kZoomIn;
	target_fov_ = target_fov;
	zoom_in_timer_->Stop();
	zoom_in_timer_->ChangeMaxTime(time);
	zoom_in_timer_->ReStart();
	zoom_timer_->Stop();
	zoom_timer_->ChangeMaxTime(active_time);
	zoom_out_timer_->Stop();
	zoom_out_timer_->ChangeMaxTime(time);
}

void Zoom::SetCurrentFov(const float& current_fov)
{
	current_fov_ = current_fov;
}

const float Zoom::GetZoomValue() const
{
	return zoom_value_;
}

void Zoom::ZoomInUpdate()
{
	zoom_in_timer_->Update();
	auto fov_diff = (target_fov_ - current_fov_);
	if (zoom_in_timer_->GetIsEnd())
	{
		zoom_value_ = fov_diff;
		state_ = ZoomState::kZoom;
		zoom_timer_->ReStart();
	}
	else
	{
		zoom_value_ = fov_diff * zoom_in_timer_->GetRatio();
	}
}

void Zoom::ZoomUpdate()
{
	zoom_value_ = 0.f;
	zoom_timer_->Update();

	if (zoom_timer_->GetIsEnd())
	{
		state_ = ZoomState::kZoomOut;
		target_fov_ = 75.f;
		zoom_out_timer_->ReStart();
	}
}

void Zoom::ZoomOutUpdate()
{
	zoom_out_timer_->Update();
	auto fov_diff = (target_fov_ - current_fov_);
	if (zoom_out_timer_->GetIsEnd())
	{
		zoom_value_ = fov_diff;
		state_ = ZoomState::kNotActive;
	}
	else
	{
		zoom_value_ = fov_diff * zoom_out_timer_->GetRatio();
	}
}