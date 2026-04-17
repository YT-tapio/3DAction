#include<iostream>
#include<vector>
#include<map>
#include"DxLib.h"
#include"attack_correction.h"
#include"player.h"
#include"enemy_base.h"
#include"vector_assistant.h"

bool AttackCorrection::ApproachTheEnemy(std::vector<std::shared_ptr<ObjectBase>> objects, 
	std::shared_ptr<Player> player, VECTOR& velocity, float speed, float move_ratio, float detection_dist)
{
	// objectsの中に敵がいるのかの判断をする
	std::map<float, VECTOR> dist_pos_mp;
	VECTOR my_pos = player->GetPosition();

	for (auto& object : objects)
	{
		auto enemy = std::dynamic_pointer_cast<EnemyBase>(object);
		if (enemy == nullptr) { continue; }
		float dist_size = 0.f;
		VECTOR enemy_pos = enemy->GetPosition();
		dist_size = VSize(VSub(enemy_pos, my_pos));
		dist_pos_mp[dist_size] = enemy_pos;
	}

	if (dist_pos_mp.empty()) { return FALSE; }

	float dist_size = dist_pos_mp.begin()->first;
	// 近すぎるとスピードが発生しないエリアを設定する
	
	float ratio = dist_size / detection_dist;
	
	VECTOR dir = VectorAssistant::VGetDir(my_pos, dist_pos_mp.begin()->second);

	if (ratio > move_ratio)
	{
		velocity = VScale(dir, speed* ratio);
	}
	else
	{
		velocity = VectorAssistant::VGetZero();
		return TRUE;
	}

	return TRUE;
}

AttackCorrection::AttackCorrection()
{

}