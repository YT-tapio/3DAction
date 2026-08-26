#include<fstream>
#include<sstream>
#include"DxLib.h"
#include"shadow_circle.h"
#include"vector_assistant.h"
#include"csv_file_assistant.h"
#include"object_setter.h"

ShadowCircle::ShadowCircle(VECTOR* owner_pos,const float& size)
	: owner_pos_(owner_pos)
	, pos_(VectorAssistant::VGetZero())
	, rot_(VectorAssistant::VGetZero())
	, scale_(VGet(size,1.f,size))
	, blend_rate_(0.f)
{
	LoadFile();
	// object_setterへ自身を登録
	ObjectSetter::GetInstance().AddResource(handle_, &pos_, &rot_, &scale_);
}

ShadowCircle::~ShadowCircle()
{
	// リソースの開放
	MV1DeleteModel(handle_);
}

void ShadowCircle::Init()
{

}

void ShadowCircle::Update()
{
	// ポジションの更新
	pos_ = *owner_pos_;
	pos_.y = base_y_;
}

const void ShadowCircle::Draw() const
{
	MV1SetOpacityRate(handle_, blend_rate_);
	MV1DrawModel(handle_);
}

void ShadowCircle::LoadFile()
{
	std::ifstream file("data/csv/shadow/shadow_circle_data.csv");
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
		return;
	}

	// 最初の行を飛ばす
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;

		auto path = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		handle_ = MV1LoadModel(path.c_str());
		base_y_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		blend_rate_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		if (handle_ == -1)
		{ 
			printfDx("読み込み失敗\n");
			return;
		}
	}
}
