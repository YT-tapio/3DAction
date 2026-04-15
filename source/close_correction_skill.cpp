#include<memory>
#include<vector>
#include<map>
#include<string>
#include"close_correction_skill.h"
#include"object_base.h"
#include"player.h"
#include"check_my_area.h"
#include"enemy_base.h"
#include"vector_assistant.h"

CloseCorrectionSkill::CloseCorrectionSkill(std::weak_ptr<Player> owner, std::shared_ptr<BehaviorBase> behaivor)
	: CorrectionSkill(owner, behaivor)
{

}

CloseCorrectionSkill::~CloseCorrectionSkill()
{

}

void CloseCorrectionSkill::Init()
{

}

void CloseCorrectionSkill::Update()
{

}

void CloseCorrectionSkill::Draw()
{

}

void CloseCorrectionSkill::Debug()
{

}

void CloseCorrectionSkill::Correction()
{
	
	//周りにobjectがあるかどうかを調べる
	auto owner = owner_.lock();
	auto area_object = owner->GetMyAreaObject();

	std::map<float, VECTOR> object_dist_dir_mp;

	for (const auto& object : area_object)
	{
		std::shared_ptr<ObjectBase> obj = object.lock();
		if (obj == nullptr) { continue; }
		auto enemy = std::dynamic_pointer_cast<EnemyBase>(obj);
		if (enemy == nullptr) { continue; }
		float dist = 0;
		VECTOR obj_pos = obj->GetPosition();
		VECTOR dist_vec = VSub(obj_pos, owner->GetPosition());
		VECTOR obj_dir = VNorm(dist_vec);
		dist = VSize(dist_vec);
		object_dist_dir_mp[dist] = obj_dir;
		// object_dist_pos_mp[dist] = obj_pos;
	}

	if (object_dist_dir_mp.size() == 0) { return; }
	owner->ResetVelocity();

	//この割合だと調整しない
	const float kRatioMin	= 0.45f;
	float detection_radius_ = owner->GetDetectionRadius(); //検出範囲
	float speed = 19.5f;
	float most_near_dist = object_dist_dir_mp.begin()->first;		// 一番近い敵との距離
	float speed_ratio = most_near_dist / detection_radius_;

	// 距離が近すぎると終わる進ませない
	if (speed_ratio < kRatioMin)
	{
		speed = 0.f;
	}
	else
	{
		float offset_detection_radius = detection_radius_ - (detection_radius_ * kRatioMin);
		float offset_most_near_dist = most_near_dist - (detection_radius_ * kRatioMin);
		speed_ratio = offset_most_near_dist / offset_detection_radius;
		speed = speed * speed_ratio;				// 距離によってspeedを変える
		speed = speed;
	}

	//一番近い奴の情報を受け取る
	VECTOR target_dir = object_dist_dir_mp.begin()->second;
	//VECTOR target_pos_ = object_dist_pos_mp.begin()->second;


	VECTOR vel = VScale(target_dir, speed);
	owner->SetRotation(VGet(0.f, VectorAssistant::VGetTan(VectorAssistant::VGetReverce(target_dir)), 0.f));
	owner->SetDirection(target_dir);
	owner->SetVelocity(vel);

}

