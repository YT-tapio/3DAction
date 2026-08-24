#include<string>
#include<fstream>
#include<sstream>
#include"DxLib.h"
#include"object_3D.h"
#include"attack_range_rectangle.h"
#include"vector_assistant.h"
#include"object_setter.h"
#include"csv_file_assistant.h"

AttackRangeRectangle::AttackRangeRectangle()
	: AttackRange()
{

}

AttackRangeRectangle::~AttackRangeRectangle()
{

}

void AttackRangeRectangle::Active(const VECTOR& pos, const VECTOR& scale)
{
	pos_ = pos;
	scale_ = VectorAssistant::VGetSame(1.f);
	target_scale_ = scale;
}

void AttackRangeRectangle::LoadFile()
{
	std::ifstream file("data/csv/attack_range/attack_range_rectangle.csv");
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