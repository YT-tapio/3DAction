#include<fstream>
#include<sstream>
#include<string>
#include"DxLib.h"
#include"status.h"
#include"status_container.h"
#include"csv_file_assistant.h"
#include"condition_timer.h"
#include"variable_timer.h"
#include"buff_type.h"
#include"attack_type.h"
#include"debug.h"
#include"color.h"
#include"vector_assistant.h"

StatusContainer::StatusContainer(const std::string owner_name,const VECTOR& hp_pos, const VECTOR& hp_size)
	: base_status_{}
	, current_status_{}
	,hp_pos_(hp_pos)
	, hp_size_(hp_size)
{
	LoadFile(owner_name);
	Init();
}

StatusContainer::~StatusContainer()
{
	
}

void StatusContainer::Init()
{
	current_status_ = base_status_;
}

void StatusContainer::Update()
{
	// バフされる量をあらかじめ決めておく

}

void StatusContainer::Draw()
{
	// HPの描画
	// 棒状のものが減るようにして、下の方にhpの数値を書くような形で

	// 右上のpos
	VECTOR box_right_pos = VectorAssistant::VGet2D((hp_pos_.x - (hp_size_.x * 0.5f)), (hp_pos_.y - (hp_size_.y * 0.5f)));

	// 後ろのものmaxまで表示されるもの
	DrawBox(static_cast<int>(box_right_pos.x),
		static_cast<int>(box_right_pos.y),
		static_cast<int>(box_right_pos.x + hp_size_.x),
		static_cast<int>(box_right_pos.y + hp_size_.y),
		GetColor(255, 0, 0), TRUE);

	float hp_size_x = 0;
	
	if (current_status_.hp > 0)
	{
		hp_size_x = hp_size_.x * (current_status_.hp / base_status_.hp);

		DrawBox(static_cast<int>(box_right_pos.x),
			static_cast<int>(box_right_pos.y),
			static_cast<int>(box_right_pos.x + hp_size_x),
			static_cast<int>(box_right_pos.y + hp_size_.y),
			GetColor(0, 220, 30), TRUE);
	}

	// 下にhpの実数値を描画
	VECTOR hp_num_pos = VectorAssistant::VGet2D(hp_pos_.x - (hp_size_.x * 0.5f), hp_pos_.y + (hp_size_.y * 0.5f) + 2.f);
	DrawFormatString(static_cast<int>(hp_num_pos.x), static_cast<int>(hp_num_pos.y),
		GetColor(0, 0, 3), "HP：%d", static_cast<int>(current_status_.hp));
}

void StatusContainer::Debug()
{
	// 
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "-----current_status-----", Color::kWhite);
	Debug::GetInstance().Add();
	
	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "HP：%.2f",current_status_.hp);
	Debug::GetInstance().Add();

	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "PhysicalATK：%.2f",current_status_.physical_atk);
	Debug::GetInstance().Add();

	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "PhysicalDEF：%.2f", current_status_.physical_def);
	Debug::GetInstance().Add();

	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "MagicATK：%.2f", current_status_.magic_atk);
	Debug::GetInstance().Add();

	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "MagicDEF：%.2f", current_status_.magic_def);
	Debug::GetInstance().Add();

	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "Stamina：%.2f", current_status_.stamina);
	Debug::GetInstance().Add();
	
	/*
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "-----base_status-----", Color::kWhite);
	Debug::GetInstance().Add();
	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "HP：%.2f", base_status_.hp);
	Debug::GetInstance().Add();

	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "PhysicalATK：%.2f", base_status_.physical_atk);
	Debug::GetInstance().Add();

	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "PhysicalDEF：%.2f", base_status_.physical_def);
	Debug::GetInstance().Add();

	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "MagicATK：%.2f", base_status_.magic_atk);
	Debug::GetInstance().Add();

	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "MagicDEF：%.2f", base_status_.magic_def);
	Debug::GetInstance().Add();

	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "Stamina：%.2f", base_status_.stamina);
	Debug::GetInstance().Add();
	*/
	


}

void StatusContainer::TakeDamage(float atk,AttackType type)
{
	// 攻撃力と防御力の計算を行う
	float damage = 0.f;

	switch (type)
	{
	case AttackType::kPhysical:
		damage = atk - current_status_.physical_def;
		break;

	case AttackType::kMagic:
		damage = atk - current_status_.magic_def;
		break;
	}

	// 最低でも1ダメージは食らう
	if (damage <= 0.f) { damage = 1.f; }

	// TODO：受けたダメージの表示する

	current_status_.hp -= damage;
	if (current_status_.hp < 0.f) { current_status_.hp = 0.f; }
}

void StatusContainer::TakeHeal(float heal)
{
	current_status_.hp += heal;

	if (current_status_.hp > base_status_.hp) { current_status_.hp = base_status_.hp; }
}

const Status StatusContainer::GetBaseStatus() const
{
	return base_status_;
}

const Status StatusContainer::GetCurrentStatus() const
{
	return current_status_;
}

void StatusContainer::LoadFile(const std::string owner_name)
{
	// データ読み取り
	
	const std::string file_path = "data/csv/status/status_data.csv";

	std::ifstream file(file_path);
	std::string line;

	if (!file)
	{
		printfDx("csvファイル(status) 読み込み失敗\n");
	}

	// 最初の行は飛ばす
	std::getline(file, line);

	// 検索外の場合のフラグ
	bool is_empty = TRUE;

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		if (owner_name != CSVFileAssistant::GetStringOfCSVFile(ss, data)) { continue; }

		// データを用意
		Status base_data = {};
		
		base_data.hp			= CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		base_data.physical_atk	= CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		base_data.physical_def	= CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		base_data.magic_atk		= CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		base_data.magic_def		= CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		base_data.stamina		= CSVFileAssistant::GetFloatOfCSVFile(ss, data);

		base_status_ = base_data;
		is_empty = FALSE;

		break;
	}

	if (is_empty)
	{
		printfDx("そのようなゲーム内キャラクターはいません\n");
	}

	// ファイルを閉じる

}

