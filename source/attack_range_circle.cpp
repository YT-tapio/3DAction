#include<string>
#include<fstream>
#include<sstream>
#include"DxLib.h"
#include<functional>
#include"object_3D.h"
#include"attack_range_circle.h"
#include"vector_assistant.h"
#include"object_setter.h"
#include"csv_file_assistant.h"
#include"lerp.h"
#include"condition_timer.h"
#include"variable_timer.h"

AttackRangeCircle::AttackRangeCircle()
	: AttackRange()
{
	LoadFile();
	scale_ = VectorAssistant::VGetSame(1.f); 
	// objectsetter‚Ö“o˜^
	ObjectSetter::GetInstance().AddResource(handle_, &pos_, &rot_, &scale_);
	ObjectSetter::GetInstance().AddResource(leading_up_attack_handle_, &leading_up_pos_, 
		&leading_up_rot_, &leading_up_scale_);
	leading_up_base_size_ = 0.01f;
}

AttackRangeCircle::~AttackRangeCircle()
{

}

void AttackRangeCircle::Update()
{
	if (VSize(target_scale_) == 0) { return; }					// ƒ^[ƒQƒbƒg‚ğ•ÏX‚µ‚Ä‚¢‚È‚¢‚Ì‚È‚ç
	// if (VSize(target_scale_) == VSize(scale_)) { return; }	// ˆê‚É‚È‚Á‚½‚çœŠO

	timer_->Update();

	// Damp‚·‚é
	scale_ = Lerp::DampV(scale_, target_scale_, 0.4f);
	leading_up_scale_ = VScale(target_scale_, leading_up_base_size_ * timer_->GetRatio());
}

void AttackRangeCircle::Active(const VECTOR& pos, const VECTOR scale, const float& time)
{
	pos_ = pos;
	leading_up_pos_ = VAdd(pos_,VGet(0.f,0.05f,0.f));
	scale_ = VectorAssistant::VGetSame(1.f);
	leading_up_scale_ = VectorAssistant::VGetZero();
	target_scale_ = scale;
	timer_->Stop();
	timer_->ChangeMaxTime(time);
	timer_->ReStart();
}

void AttackRangeCircle::SetPos(const VECTOR& pos)
{
	pos_ = pos;
	leading_up_pos_ = pos_;
}

void AttackRangeCircle::LoadFile()
{
	std::ifstream file("data/csv/attack_range/attack_range.csv");
	std::string line;

	if (!file)
	{
		printfDx("csvƒtƒ@ƒCƒ‹“Ç‚İ‚İ¸”s\n");
		return;
	}

	// Å‰‚Ì2s‚ğ”ò‚Î‚·
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;
		std::string name;
		name = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		handle_ = MV1LoadModel(name.c_str());
		if (handle_ == -1) { printfDx("“Ç‚İ‚İ¸”s\n"); }
		auto leading_up_attack_path = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		leading_up_attack_handle_ = MV1LoadModel(leading_up_attack_path.c_str());
		if (leading_up_attack_handle_ == -1) { printfDx("“Ç‚İ‚İ¸”s"); }
	}
}