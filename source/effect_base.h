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

	void Draw();

	void Debug();

	const bool GetIsPlay() const;

protected:

	

private:

	void SetTransform();

	EffectData data_;

	bool is_play_;
	bool is_stop_;

	int end_id_;

};