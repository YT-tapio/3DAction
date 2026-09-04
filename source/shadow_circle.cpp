#include<fstream>
#include<sstream>
#include"DxLib.h"
#include"shadow_circle.h"
#include"vector_assistant.h"
#include"csv_file_assistant.h"
#include<unordered_map>
#include"load_csv_file.h"
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
	if (handle_ != -1)
	{
		// リソースの開放
		MV1DeleteModel(handle_);
		handle_ = -1;
	}
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
	const std::string file_path = "data/csv/shadow/shadow_circle_data.csv";
	auto datas = LoadCSVFile::GetInstance().GetData(file_path, 1).string_datas;
	
	auto model_path = datas[0];
	handle_ = MV1LoadModel(model_path.c_str());
	base_y_ = stof(datas[1]);
	blend_rate_ = stof(datas[2]);
	if (handle_ == -1) { printfDx("モデル読み込み失敗\n"); }
	
}
