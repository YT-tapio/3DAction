#pragma once

struct AnimationData
{
	int handle;			// アニメーションのモデル
	int anim_index;		// そのモデルにあるアニメーションの番号
	int attach_index;	// attachした際のデータ。

	int priority;		// 優先度

	float play_time;	// 現在の再生時間
	float total_time;	// 上限時間
	float play_speed;	// 再生速度
	float cancel_time;

	bool loop;
};