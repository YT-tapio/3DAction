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

AttackRangeCircle::AttackRangeCircle()
	: AttackRange()
{
	LoadFile();
	scale_ = VectorAssistant::VGetSame(1.f); 
	// objectsetterÇ÷ìoò^
	ObjectSetter::GetInstance().AddResource(handle_, &pos_, &rot_, &scale_);
	ObjectSetter::GetInstance().AddResource(leading_up_attack_handle_, &leading_up_pos_, 
		&leading_up_rot_, &leading_up_scale_);
}

AttackRangeCircle::~AttackRangeCircle()
{

}

void AttackRangeCircle::Active(const VECTOR& pos, const VECTOR scale, std::function<float()> ratio)
{
	pos_ = pos;
	scale_ = VectorAssistant::VGetSame(1.f);
	target_scale_ = scale;
	leading_up_pos_ = pos_;
	leading_up_ratio_ = ratio;
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
		printfDx("csvÉtÉ@ÉCÉãì«Ç›çûÇ›é∏îs\n");
		return;
	}

	// ç≈èâÇÃ2çsÇîÚÇŒÇ∑
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;
		std::string name;
		name = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		handle_ = MV1LoadModel(name.c_str());
		if (handle_ == -1) { printfDx("ì«Ç›çûÇ›é∏îs\n"); }
	}
}