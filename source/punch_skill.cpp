#include<iostream>
#include<memory>
#include"DxLib.h"
#include"player.h"
#include"punch_skill.h"
#include"punch.h"
#include"rigid_body.h"
#include"sphere.h"

PunchSkill::PunchSkill(std::weak_ptr<Player>owner,VECTOR* pos,const float r)
	: SkillBase(owner,std::make_shared<Punch>(owner,pos,std::make_shared<RigidBody>(std::make_shared<Sphere>(r,VGet(0,0,0)), pos, FALSE, TRUE, 1.f)))
{

}

PunchSkill::~PunchSkill()
{

}

void PunchSkill::Init()
{

}

void PunchSkill::Update()
{

}

void PunchSkill::Draw()
{

}

void PunchSkill::Debug()
{

}

