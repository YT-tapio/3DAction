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
	LoadFile();
	scale_ = VectorAssistant::VGetSame(1.f);
	// objectsetterへ登録
	ObjectSetter::GetInstance().AddResource(handle_,&pos_,&rot_,&scale_);
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

void AttackRange::Init(const VECTOR& pos, const VECTOR& scale)
{
	pos_				= pos;
	scale_ = VectorAssistant::VGetSame(1.f);
	target_scale_	= scale;
}

void AttackRange::Update()
{
	if (VSize(target_scale_) == 0) { return; }					// ターゲットを変更していないのなら
	if (VSize(target_scale_) == VSize(scale_)) { return; }	// 一緒になったら除外

	// Dampする
	scale_ = Lerp::DampV(scale_, target_scale_, 0.4f);
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

void AttackRange::LoadFile()
{
	std::ifstream file("data/csv/attack_range/attack_range.csv");
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
		return;
	}

	// 最初の2行を飛ばす
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;
		std::string name;
		name = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		handle_ = MV1LoadModel(name.c_str());
		if (handle_ == -1) { printfDx("読み込み失敗\n"); }
	}
}