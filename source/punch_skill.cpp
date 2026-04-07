#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<unordered_map>
#include<vector>
#include<memory>
#include"DxLib.h"
#include"object_base.h"
#include"player.h"
#include"punch_skill.h"
#include"punch.h"
#include"rigid_body.h"
#include"sphere.h"
#include"input_base.h"
#include"animator_base.h"
#include"enemy_base.h"
#include"vector_assistant.h"
#include"FPS.h"

PunchSkill::PunchSkill(std::weak_ptr<Player> owner,VECTOR* pos,const float r,const float detection_radius)
	: SkillBase(owner,std::make_shared<Punch>(owner,pos,std::make_shared<RigidBody>(std::make_shared<Sphere>(r,VGet(0,0,0)), pos, FALSE, TRUE, 1.f)))
{
	target_dir_ = VectorAssistant::VGetZero();
	target_pos_ = VectorAssistant::VGetZero();
	detection_radius_ = detection_radius;
}

PunchSkill::~PunchSkill()
{

}

void PunchSkill::Init()
{
	behavior_->Init();
}

void PunchSkill::Update()
{
	auto owner = owner_.lock();

	if(owner == nullptr)
	{
		printfDx("player以外にはskillを適応できません\n");
		return;
	}

	if (is_active_)
	{
		// skillが終わる条件
		if (owner->GetAnimator()->GetNowAnimName() != "punch")
		{
			is_active_ = FALSE;
			owner->SetIsStop(FALSE);
		}
	}

	
	if(!is_active_)
	{
		if (CheckIsPunch(owner))
		{
			is_active_ = TRUE;
			// punchさせる
			owner->GetAnimator()->PlayRequest("punch");	//パンチのanimationを再生をお願いする
			
			// この瞬間にplayerをうごかす
			auto owner_area_object = owner->GetMyAreaObject();
			DecideTarget(owner_area_object,owner);
			owner->SetIsStop(TRUE);
		}
	}
	// behaviorのupdate
	behavior_->Update();
}

void PunchSkill::Draw()
{

}

void PunchSkill::Debug()
{
	DrawSphere3D(target_pos_, 3.f, 20, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
	behavior_->Debug();
}

void PunchSkill::DecideTarget(std::vector<std::weak_ptr<ObjectBase>> owner_area_objects,std::shared_ptr<Player> owner)
{
	std::map<float, VECTOR> object_dist_dir_mp;
	std::map<float, VECTOR> object_dist_pos_mp;
	for (const auto& object : owner_area_objects)
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
		object_dist_pos_mp[dist] = obj_pos;
	}

	if (object_dist_dir_mp.size() == 0) { return; }

	owner->ResetVelocity();

	//この割合だと調整しない
	const float kRatioMin = 0.45f;

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
		float offset_detection_radius	= detection_radius_ - (detection_radius_ * kRatioMin);
		float offset_most_near_dist		= most_near_dist - (detection_radius_ * kRatioMin);
		speed_ratio = offset_most_near_dist / offset_detection_radius;
		speed = speed * speed_ratio;				// 距離によってspeedを変える
		speed = speed;
	}

	//一番近い奴の情報を受け取る
	target_dir_		= object_dist_dir_mp.begin()->second;
	target_pos_		= object_dist_pos_mp.begin()->second;
	

	VECTOR vel = VScale(target_dir_, speed);
	owner->SetRotation(VGet(0.f, VectorAssistant::VGetTan(VectorAssistant::VGetReverce(target_dir_)), 0.f));
	owner->SetDirection(target_dir_);
	//owner->ResetVelocity();
	owner->SetVelocity(vel);
}

bool PunchSkill::CheckIsPunch(std::shared_ptr<Player> owner)
{
	if (owner->GetIsStop())										{ return FALSE; }
	if (!owner->GetIsGround())									{ return FALSE; }	// 着地していない
	if (owner->GetIsInvincible())								{ return FALSE; }
	if (owner->GetAnimator()->GetNowAnimName() == "punch")		{ return FALSE; }	// パンチじゃない
	if (!owner->GetInput()->IsNormalSkill())							{ return FALSE; }	// 入力されているか

	return TRUE;
}
