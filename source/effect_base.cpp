#include<fstream>
#include<sstream>
#include<string>
#include"DxLib.h"
#include"EffekseerForDxLib.h"
#include"effect_base.h"
#include"effect_end_state.h"
#include"vector_assistant.h"
#include"csv_file_assistant.h"
#include"FPS.h"

EffectBase::EffectBase(EffectData data)
	: data_(data)
	, is_play_(FALSE)
	, is_stop_(FALSE)
	, end_id_(EffectEndState::kNothing)
{
	
}

EffectBase::~EffectBase()
{
	StopEffekseer3DEffect(data_.playing_handle);
	DeleteEffekseerEffect(data_.playing_handle);
	DeleteEffekseerEffect(data_.handle);
}

void EffectBase::Init()
{
	
	is_play_ = FALSE;
	is_stop_ = FALSE;
}

void EffectBase::Update()
{
	if (!is_play_) { return; }
	// ‚¢‚Á‚½‚ñÄ¶‚Å‚«‚é‚æ‚¤‚É‚µ‚æ‚¤
	float speed = data_.speed * (FPS::GetInstance().GetDeltaTime() * 60.f);
	if (is_stop_) { speed = 0.f; }

	if (end_id_ == EffectEndState::kMoment)
	{
		data_.playing_handle = StopEffekseer3DEffect(data_.playing_handle);
		data_.play_time = 0.f;
		is_play_ = FALSE;
		return;
	}

	data_.play_time += speed;
	SetSpeedPlayingEffekseer3DEffect(data_.playing_handle,speed);
	SetTransform();

	if (data_.play_time > data_.total_time)
	{
		data_.playing_handle = StopEffekseer3DEffect(data_.playing_handle);
		if (data_.loop)
		{
			if (end_id_ == EffectEndState::kTotal)
			{
				data_.playing_handle = StopEffekseer3DEffect(data_.playing_handle);
				data_.play_time = 0.f;
				is_play_ = FALSE;
				return;
			}
			data_.playing_handle = PlayEffekseer3DEffect(data_.handle);
			data_.play_time = data_.play_time - data_.total_time;
			SetSpeedPlayingEffekseer3DEffect(data_.playing_handle, data_.play_time);
		}
		else
		{
			is_play_ = FALSE;
		}
	}
}

void EffectBase::Play()
{
	if (is_play_) { return; }
	data_.playing_handle = PlayEffekseer3DEffect(data_.handle);
	is_play_ = TRUE;
	data_.play_time = 0.f;
	end_id_ = EffectEndState::kNothing;
}

void EffectBase::Stop()
{
	if (!is_play_) { return; }
	is_stop_ = TRUE;
}

void EffectBase::End(const int& end_id)
{
	if (!is_play_) { return; }
	end_id_ = end_id;
}

void EffectBase::RePlay()
{
	is_stop_ = FALSE;
}

void EffectBase::SetPos(const VECTOR& pos)
{
	data_.pos = pos;
}

void EffectBase::SetRot(const VECTOR& rot)
{
	data_.rot = rot;
}

void EffectBase::SetScale(const VECTOR& scale)
{
	data_.scale = scale;
}

void EffectBase::Draw()
{
	if (!is_play_) { return; }
	DrawEffekseer3D_Draw(data_.playing_handle);
}

void EffectBase::Debug()
{

}

const bool EffectBase::GetIsPlay() const
{
	return is_play_;
}

void EffectBase::SetTransform()
{
	SetScalePlayingEffekseer3DEffect(data_.playing_handle, data_.scale.x, data_.scale.y, data_.scale.z);
	SetRotationPlayingEffekseer3DEffect(data_.playing_handle, data_.rot.x, data_.rot.y, data_.rot.z);
	SetPosPlayingEffekseer3DEffect(data_.playing_handle, data_.pos.x, data_.pos.y, data_.pos.z);
}
