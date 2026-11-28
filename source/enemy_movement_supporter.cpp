#include<memory>
#include<vector>
#include<string>
#include"DxLib.h"
#include"enemy_movement_supporter.h"
#include"enemy_base.h"
#include"status.h"
#include"status_container.h"
#include"vector_assistant.h"

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

VECTOR EnemyMovementSupporter::SupportMovement(EnemyBase* support_enemy,const VECTOR& target_pos,const VECTOR& move_dir)
{
	auto support_dir = move_dir;

	for (auto enemy : enemies_)
	{
		// ¶‚«‚Ä‚¢‚é‚©
		if (enemy->GetStatusContainer()->GetCurrentStatus().hp == 0.f) { continue; }
		auto my_pos = support_enemy->GetPosition();
		auto other_pos = enemy->GetPosition();
		auto dist = VSub(other_pos, my_pos);
		auto rad = VectorAssistant::GetTwoVectorRad(move_dir,dist);
		const auto kInRad = 10.f;
		// ”ÍˆÍ“à‚É“G‚ª‚¢‚é‚È‚ç‰ñ‚è‚Ş
		if (rad < kInRad)
		{
			// ‰E‚à‚µ‚­‚Í¶‚É‰ñ‚è‚Ş
			auto cross = VectorAssistant::VGetCross(my_pos, other_pos);

			// ‰ñ‚è‚ŞŠp“x(‰½‚à‚µ‚È‚¢‚È‚ç‰E)
			auto rot_rad = 40.f;
			// •Ï‚¦‚é
			if (cross.y > 0.f)
			{
				// ¶
				rot_rad = -rot_rad;
			}
			
			support_dir = VectorAssistant::VGetRotRadY(support_dir, rot_rad);
		}
	}

	return support_dir;
}

