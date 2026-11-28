#include<memory>
#include<vector>
#include<string>
#include"DxLib.h"
#include"enemy_movement_supporter.h"
#include"enemy_base.h"
#include"status.h"
#include"status_container.h"
#include"vector_assistant.h"
#include"cpplinq.hpp"

EnemyMovementSupporter::EnemyMovementSupporter()
{

}

EnemyMovementSupporter::~EnemyMovementSupporter()
{
	enemies_.clear();
}

void EnemyMovementSupporter::AddResource(EnemyBase* enemy)
{
	enemies_.emplace_back(enemy);
}

VECTOR EnemyMovementSupporter::SupportMovement(EnemyBase* movement_enemy,const VECTOR& target_pos)
{
	auto my_pos = movement_enemy->GetPosition();
	auto support_dir = VNorm(VSub(target_pos, my_pos));

	auto isTargetEnemy = [movement_enemy,target_pos,my_pos](EnemyBase* enemy)
		{
			auto is_same = (enemy == movement_enemy);
			auto is_active = enemy->GetIsActive();
			auto is_alive = enemy->GetStatusContainer()->GetIsAlive();
			// ターゲットから自身と、ターゲットからほかの敵の距離を比べ近い場合は追加
			auto enemy_pos = enemy->GetPosition();
			auto me_to_target_dist = VSize(VSub(target_pos, my_pos));
			auto target_to_enemy_dist = VSize(VSub(target_pos, enemy_pos));
			auto is_near = me_to_target_dist > target_to_enemy_dist;
			return !is_same || is_active || is_alive || is_near;
		};

	auto activate_enemies = linq::from(enemies_)
		.where(isTargetEnemy)
		.to_vector();

	for (auto enemy : activate_enemies)
	{
		auto other_pos = enemy->GetPosition();
		auto dist = VSub(other_pos, my_pos);
		auto rad = VectorAssistant::GetTwoVectorRad(support_dir, dist);
		const auto kInRad = 10.f;
		// 範囲内に敵がいるなら回り込む
		if (rad < kInRad)
		{
			// 右もしくは左に回り込む
			auto cross = VectorAssistant::VGetCross(my_pos, other_pos);

			// 回り込む角度(何もしないなら右)
			auto rot_rad = 40.f;
			// 変える
			if (cross.y > 0.f)
			{
				// 左
				rot_rad = -rot_rad;
			}
			support_dir = VectorAssistant::VGetRotRadY(support_dir, rot_rad);
		}
	}

	/*
	for (auto enemy : enemies_)
	{
		if (!enemy->GetIsActive()) { continue; }
		if (enemy->GetStatusContainer()->GetIsAlive()) { continue; }
		if (enemy == movement_enemy) { continue; }
		auto other_pos = enemy->GetPosition();
		auto dist = VSub(other_pos, my_pos);
		auto rad = VectorAssistant::GetTwoVectorRad(support_dir,dist);
		const auto kInRad = 10.f;
		// 範囲内に敵がいるなら回り込む
		if (rad < kInRad)
		{
			// 右もしくは左に回り込む
			auto cross = VectorAssistant::VGetCross(my_pos, other_pos);

			// 回り込む角度(何もしないなら右)
			auto rot_rad = 40.f;
			// 変える
			if (cross.y > 0.f)
			{
				// 左
				rot_rad = -rot_rad;
			}
			support_dir = VectorAssistant::VGetRotRadY(support_dir, rot_rad);
		}
	}
	*/

	return support_dir;
}

