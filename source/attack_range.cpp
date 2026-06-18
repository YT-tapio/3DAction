#include<fstream>
#include<sstream>
#include"DxLib.h"
#include"object_3D.h"
#include"attack_range.h"
#include"object_setter.h"
#include"csv_file_assistant.h"

AttackRange::AttackRange()
	: Object3D("")
{
	LoadFile();
	// objectsetter‚Ö“o˜^
	ObjectSetter::GetInstance().AddResource(handle_,&pos_,&rot_,&scale_);
}


AttackRange::~AttackRange()
{

}

void AttackRange::Init()
{

}

void AttackRange::Update()
{

}

void AttackRange::Draw()
{
	MV1DrawModel(handle_);
}

void AttackRange::Debug()
{

}

void AttackRange::SetTransform(const VECTOR& pos, const VECTOR& rot, const VECTOR& scale)
{
	pos_ = pos;
	rot_ = rot;
	scale_ = scale;
}

void AttackRange::LoadFile()
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