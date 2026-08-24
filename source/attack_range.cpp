#include<fstream>
#include<sstream>
#include"DxLib.h"
#include"object_3D.h"
#include"attack_range.h"
#include"object_setter.h"
#include"csv_file_assistant.h"
#include"lerp.h"

AttackRange::AttackRange()
	: Object3D("")
	, target_scale_(VectorAssistant::VGetZero())
{
	
}

AttackRange::~AttackRange()
{
	MV1DeleteModel(handle_);
}

void AttackRange::Init()
{
	pos_				= VectorAssistant::VGetZero();
	scale_			= VectorAssistant::VGetSame(1.f);
	target_scale_	= VectorAssistant::VGetSame(0.f);
}

void AttackRange::Update()
{
	if (VSize(target_scale_) == 0) { return; }					// ターゲットを変更していないのなら
	if (VSize(target_scale_) == VSize(scale_)) { return; }	// 一緒になったら除外

	// Dampする
	scale_ = Lerp::DampV(scale_, target_scale_, 0.4f);
}

void AttackRange::Active(const VECTOR& pos, const VECTOR& scale)
{

}

void AttackRange::Draw()
{
	SetUseLighting(FALSE);
	MV1SetOpacityRate(handle_, 0.6f);
	MV1DrawModel(handle_);
	SetUseLighting(TRUE);
}

void AttackRange::Debug()
{

}