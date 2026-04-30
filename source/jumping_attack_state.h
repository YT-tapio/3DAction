#pragma once

enum class JumpingAttackState
{
	kStandby,		// ジャンプのよびどうさ　
	kJumping,		// ジャンプ中
	kAirStandby,	// 空中での待機
	kFalling		// 落下中
};