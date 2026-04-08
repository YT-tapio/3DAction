#include<fstream>
#include<sstream>
#include<string>
#include"DxLib.h"
#include"EffekseerForDxLib.h"
#include"effect_base.h"
#include"vector_assistant.h"
#include"csv_file_assistant.h"
#include"FPS.h"

EffectBase::EffectBase(std::string data_file_path)
	: data_file_path_(data_file_path)
	, is_play_(FALSE)
	, is_stop_(FALSE)
{
	//LoadFile();
}

EffectBase::~EffectBase()
{
	StopEffekseer3DEffect(data_.playing_handle);
	DeleteEffekseerEffect(data_.playing_handle);
	DeleteEffekseerEffect(data_.handle);
}

void EffectBase::Init()
{
	LoadFile();
	is_play_ = FALSE;
	is_stop_ = FALSE;
}

void EffectBase::Update()
{
	if (!is_play_) { return; }
	// いったん再生できるようにしよう
	float speed = data_.speed * (FPS::GetInstance().GetDeltaTime() * 60.f);
	if (is_stop_) { speed = 0.f; }
	SetSpeedPlayingEffekseer3DEffect(data_.playing_handle,speed);
	SetPosPlayingEffekseer3DEffect(data_.playing_handle, data_.pos.x, data_.pos.y, data_.pos.z);
	UpdateEffekseer3D();
}

void EffectBase::Play()
{
	if (is_play_) { return; }
	data_.playing_handle = PlayEffekseer3DEffect(data_.handle);
	is_play_ = TRUE;
}

void EffectBase::Stop()
{
	is_stop_ = TRUE;
}

void EffectBase::RePlay()
{
	is_stop_ = FALSE;
}

void EffectBase::Draw()
{
	if (!is_play_) { return; }
	DrawEffekseer3D_Begin();
	DrawEffekseer3D_Draw(data_.playing_handle);
	DrawEffekseer3D_End();
}

void EffectBase::Debug()
{

}

void EffectBase::LoadFile()
{
	std::ifstream file(data_file_path_);
	std::string line;

	if (!file)
	{
		printfDx("csvfile読み込みエラー\n");
		return;
	}

	// 2行飛ばします
	std::getline(file, line);
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう
		EffectData effect_data;
		
		// pathを受け取る
		std::getline(ss, data, ',');
		effect_data.path = data;
		effect_data.handle = LoadEffekseerEffect(effect_data.path.c_str(), 1.f);
		if (effect_data.handle == -1) { printfDx("effect読み込み失敗\n"); }
		effect_data.pos		= CSVFileAssistant::GetVectorOfCSVFile(ss, data);	// 位置
		effect_data.rot		= CSVFileAssistant::GetVectorOfCSVFile(ss, data);	// 回転
		effect_data.scale	= CSVFileAssistant::GetVectorOfCSVFile(ss, data);	// 大きさ

		// spedを受け取る
		effect_data.speed = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		effect_data.play_time = 0.f;				// 再生時間を初期化

		effect_data.loop = CSVFileAssistant::GetBoolOfCSVFile(ss, data);	// 
		data_ = effect_data;
	}


}