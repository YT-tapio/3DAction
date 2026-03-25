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

PunchSkill::PunchSkill(std::weak_ptr<Player>owner,VECTOR* pos,const float r)
	: SkillBase(owner,std::make_shared<Punch>(owner,pos,std::make_shared<RigidBody>(std::make_shared<Sphere>(r,VGet(0,0,0)), pos, FALSE, TRUE, 1.f)))
{
	target_dir_ = VectorAssistant::VGetZero();
	target_pos_ = VectorAssistant::VGetZero();
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

	// skillが終わる条件
	if (owner->GetAnimator()->GetNowAnimName() != "punch")
	{
		is_active_ = FALSE;
	}

	owner->SetIsStop(FALSE);

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
		}
		else
		{
			
			return;
		}
	}
	

	//　behaviorのupdate
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
		dist = VSize(dist_vec);
		object_dist_dir_mp[dist] = VNorm(dist_vec);
		object_dist_pos_mp[dist] = obj_pos;
	}

	if (object_dist_dir_mp.size() == 0) { return; }

	target_dir_ = object_dist_dir_mp.begin()->second;
	target_pos_ = object_dist_pos_mp.begin()->second;

	owner->SetVelocity(VScale(target_dir_,10.f));
	owner->SetIsStop(TRUE);

}

bool PunchSkill::CheckIsPunch(std::shared_ptr<Player> owner)
{
	if (!owner->GetIsGround())														{ return FALSE; }	// 着地していない
	if (owner->GetAnimator()->GetNowAnimName() == "punch")		{ return FALSE; }	// パンチじゃない
	if (!owner->GetInput()->IsPunch())											{ return FALSE; }	// 入力されているか

	return TRUE;
}
