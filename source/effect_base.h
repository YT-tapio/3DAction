#pragma once
#include"effect_data.h"

class EffectBase
{
public:

	EffectBase(EffectData data);

	~EffectBase();

	void Init();

	void Update();

	void Play();

	void Stop();

	void End(const int& end_id);

	void RePlay();

	void SetPos(const VECTOR& pos);

	void SetRot(const VECTOR& rot);

	void SetScale(const VECTOR& scale);

	void Draw();

	void Debug();

	const float GetRatio() const;

	const bool GetIsPlay() const;

	const bool GetIsEnd() const;

protected:

	

private:

	void SetTransform();

	EffectData data_;

	bool is_play_;
	bool is_stop_;
	bool is_end_;

	int end_id_;

};