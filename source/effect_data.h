#pragma once

struct EffectData
{
	std::string path;		// fileの場所
	int handle;				// モデルデータ
	int playing_handle;	//再生中のデータ

	VECTOR pos;			// 位置
	VECTOR rot;			// 回転
	VECTOR scale;		// サイズ

	float speed;			// 再生速度
	float play_time;		// 現在の再生時間
	float total_time;		// トータル

	bool loop;				// ループ再生か
};