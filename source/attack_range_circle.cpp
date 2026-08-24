#include<string>
#include<fstream>
#include<sstream>
#include"DxLib.h"
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
	// objectsetter‚Ö“o˜^
	ObjectSetter::GetInstance().AddResource(handle_, &pos_, &rot_, &scale_);
}

AttackRangeCircle::~AttackRangeCircle()
{

}

void AttackRangeCircle::Active(const VECTOR& pos,const VECTOR& scale)
{
	pos_ = pos;
	scale_ = VectorAssistant::VGetSame(1.f);
	target_scale_ = scale;
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
	}
}