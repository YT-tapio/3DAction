#include<iostream>
#include<vector>
#include<map>
#include"DxLib.h"
#include"attack_correction.h"
#include"player.h"
#include"enemy_base.h"
#include"vector_assistant.h"

bool AttackCorrection::ApproachTheNearestEnemy(std::shared_ptr<Player> player, VECTOR& velocity, float speed, float move_ratio)
{
	auto objects = player->GetMyAreaObject();
	float detection_dist = player->GetDetectionRadius();
	// objects‚Ì’†‚É“G‚ª‚¢‚é‚Ì‚©‚Ì”»’f‚ð‚·‚é
	std::map<float, VECTOR> dist_pos_mp;
	VECTOR my_pos = player->GetPosition();

	for (auto& object : objects)
	{
		auto enemy = std::dynamic_pointer_cast<EnemyBase>(object.lock());
		if (enemy == nullptr) { continue; }
		float dist_size = 0.f;
		VECTOR enemy_pos = enemy->GetPosition();
		dist_size = VSize(VSub(enemy_pos, my_pos));
		dist_pos_mp[dist_size] = enemy_pos;
	}

	// “G‚ª‚¢‚È‚¢‚È‚çplayer‚ÌŒü‚«‚É“®‚©‚·
	if (dist_pos_mp.empty()) 
	{ 
		VECTOR player_dir = player->GetDirection();
		velocity = VScale(player_dir, speed);
		player->ResetVelocity();
		player->SetRotation(VGet(0.f, VectorAssistant::VGetTan(VectorAssistant::VGetReverce(player_dir)), 0.f));
		player->SetDirection(player_dir);
		player->SetVelocity(velocity);
		return FALSE;
	}

	float dist_size = dist_pos_mp.begin()->first;
	
	float ratio = dist_size / detection_dist;
	VECTOR dir = VectorAssistant::VGetDir(my_pos, dist_pos_mp.begin()->second);
	
	// ratio‚ªmove_ratio‚æ‚è‰º‚ÌŽž‚Í“®‚©‚³‚È‚¢
	if (ratio < move_ratio)
	{
		ratio = 0.f;
	}
	
	velocity = VScale(dir, speed * ratio);
	player->ResetVelocity();
	player->SetRotation(VGet(0.f, VectorAssistant::VGetTan(VectorAssistant::VGetReverce(dir)), 0.f));
	player->SetDirection(dir);
	player->SetVelocity(velocity);

	return TRUE;
}

AttackCorrection::AttackCorrection()
{

}