#pragma once
#include"DxLib.h"
#include"attack_id.h"
#include"attack_phase.h"

struct AttackInfo
{
	AttackID id = AttackID::kNone;			// UŒ‚‚Ìí—Ş
	AttackPhase phase = AttackPhase::kNone;	// UŒ‚‚Ìis

	VECTOR pos = VGet(0.f, 0.f, 0.f);	// UŒ‚‚ª”­¶‚·‚éêŠ
	VECTOR dir = VGet(0.f, 0.f, 0.f);		// UŒ‚‚Ì•ûŒü

	float range = 0.f;	// UŒ‚”ÍˆÍ
};