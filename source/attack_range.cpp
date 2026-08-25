#include<fstream>
#include<sstream>
#include<functional>
#include"DxLib.h"
#include"object_3D.h"
#include"attack_range.h"
#include"object_setter.h"
#include"csv_file_assistant.h"
#include"condition_timer.h"
#include"variable_timer.h"

AttackRange::AttackRange()
	: Object3D("")
	, target_scale_(VectorAssistant::VGetZero())
	, leading_up_ratio_(nullptr)
	, leading_up_pos_(VectorAssistant::VGetZero())
	, leading_up_rot_(VectorAssistant::VGetZero())
	, leading_up_scale_(VectorAssistant::VGetZero())
	, timer_(std::make_shared<VariableTimer>(0.f))
{
	
}

AttackRange::~AttackRange()
{
	MV1DeleteModel(handle_);
	MV1DeleteModel(leading_up_attack_handle_);
}

void AttackRange::Init()
{
	pos_				= VectorAssistant::VGetZero();
	scale_			= VectorAssistant::VGetSame(1.f);
	target_scale_	= VectorAssistant::VGetSame(0.f);
}

void AttackRange::Update()
{
	
}


void AttackRange::Draw()
{
	SetUseLighting(FALSE);
	MV1SetOpacityRate(handle_, 0.6f);
	MV1SetOpacityRate(leading_up_attack_handle_, 0.6f);
	MV1DrawModel(handle_);
	MV1DrawModel(leading_up_attack_handle_);
	SetUseLighting(TRUE);
}

void AttackRange::Debug()
{

}