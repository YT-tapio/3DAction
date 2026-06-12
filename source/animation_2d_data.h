#pragma once

struct Animation2DData
{
	std::vector<int> handles;		// アニメーション
	int current_anim_index;			// 今のアニメーションがいつなのか
	int max_anim_index;				// 全ての要素
	int priority;							// 優先度
	
	float total_time;						// 合計の時間
	float play_time;						// 再生時間
	float cool_time;						// 一つの画像にかかる時間
	bool loop;								// ループ

	std::string next_anim_name;	// 次のアニメーションの名前

};