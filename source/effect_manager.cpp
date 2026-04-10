#include<fstream>
#include<sstream>
#include<string>
#include<memory>
#include<unordered_map>
#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"effect_manager.h"
#include"effect_data.h"
#include"effect_base.h"
#include"effect_id.h"
#include"csv_file_assistant.h"
#include"radian_assistant.h"

EffectManager::EffectManager()
{

}

void EffectManager::Awake()
{
	LoadFile();
}

void EffectManager::Init()
{
	
	if (effects_.empty()) { return; }
	for (auto& effect : effects_)
	{
		effect.second->Init();
	}

}

void EffectManager::Update()
{

	auto aa = GetEffekseer3DManager();

	if (effects_.empty()) { return; }
	for (auto& effect : effects_)
	{
		effect.second->Update();
	}
	UpdateEffekseer3D();
}

void EffectManager::Draw()
{
	if (effects_.empty()) { return; }
	DrawEffekseer3D_Begin();
	for (auto& effect : effects_)
	{
		effect.second->Draw();
	}
	DrawEffekseer3D_End();
}

void EffectManager::Debug()
{

}

void EffectManager::Play(const int& id)
{
	auto effect = effects_.find(id);
	if (effect != effects_.end())
	{
		effect->second->Play();
	}
}

void EffectManager::Stop(const int& id)
{
	auto effect = effects_.find(id);
	if (effect != effects_.end())
	{
		effect->second->Stop();
	}
}

void EffectManager::End(const int& id,const int& end_id)
{
	auto effect = effects_.find(id);
	if (effect != effects_.end())
	{
		effect->second->End(end_id);
	}
}

void EffectManager::RePlay(const int& id)
{
	auto effect = effects_.find(id);
	if (effect != effects_.end())
	{
		effect->second->RePlay();
	}
}

const bool EffectManager::CheckIsPlay(const int& id) const
{
	auto effect = effects_.find(id);
	if (effect != effects_.end())
	{
		return effect->second->GetIsPlay();
	}
	return FALSE;
}

void EffectManager::LoadFile()
{
	std::ifstream file("data/csv/effect/effect_No1.csv");
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
		int id = -1;

		// pathを受け取る
		id									= CSVFileAssistant::GetIntOfCSVFile(ss, data);				// id
		effect_data.path				= CSVFileAssistant::GetStringOfCSVFile(ss,data);			// 保存場所
		effect_data.handle			= LoadEffekseerEffect(effect_data.path.c_str(), 1.f);		// データ
		if (effect_data.handle == -1) { printfDx("effect読み込み失敗\n"); }						// 読み込めたか
		effect_data.pos				= CSVFileAssistant::GetVectorOfCSVFile(ss, data);		// 位置
		effect_data.rot				= CSVFileAssistant::GetVectorOfCSVFile(ss, data);		// 回転
		// rad角に直します
		effect_data.rot.x				= (RadianAssistant::kOneRad * effect_data.rot.x);
		effect_data.rot.y				= (RadianAssistant::kOneRad * effect_data.rot.y);
		effect_data.rot.z				= (RadianAssistant::kOneRad * effect_data.rot.z);

		effect_data.scale			= CSVFileAssistant::GetVectorOfCSVFile(ss, data);		// 大きさ
		effect_data.speed			= CSVFileAssistant::GetFloatOfCSVFile(ss, data);			// speed
		effect_data.play_time		= 0.f;																		// 再生時間を初期化
		effect_data.total_time		= CSVFileAssistant::GetFloatOfCSVFile(ss, data);			// effectの再生トータル時間
		effect_data.loop				= CSVFileAssistant::GetBoolOfCSVFile(ss, data);			// ループ
		effects_[id]					= std::make_shared<EffectBase>(effect_data);			// エフェクトを生成
	}


}

