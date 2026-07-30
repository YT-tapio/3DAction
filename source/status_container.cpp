#include<fstream>
#include<sstream>
#include<string>
#include<memory>
#include<vector>
#include"DxLib.h"
#include"status.h"
#include"status_container.h"
#include"csv_file_assistant.h"
#include"condition_timer.h"
#include"variable_timer.h"
#include"attack_type.h"
#include"debug.h"
#include"color.h"
#include"vector_assistant.h"
#include"FPS.h"
#include"stat_modifire_group.h"
#include"random.h"
#include"my_math.h"

StatusContainer::StatusContainer(const std::string owner_name,const VECTOR& hp_pos, const VECTOR& hp_size)
	: base_status_{}
	, current_status_{}
	, can_use_stamina_(TRUE)
	, stamina_recovery_value_(0.f)
{
	LoadFile(owner_name);
	stamina_recovery_timer_ = std::make_shared<ConditionTimer>(0.5f);
	stamina_recovery_timer_->Init();
	stamina_recovery_value_ = 1.f;
	stat_modifire_group_ = std::make_shared<ActiveStatModifireGroup>();
	Init();
}

StatusContainer::~StatusContainer()
{
	
}

void StatusContainer::Init()
{
	current_status_ = base_status_;
	stamina_recovery_timer_->Init();
	stat_modifire_group_->Init();
}

void StatusContainer::Update()
{
	// バフされる量をあらかじめ決めておく
	StaminaUpdate();
	stat_modifire_group_->Update(base_status_, current_status_);
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

void StatusContainer::StaminaDown(const float down_value)
{
	current_status_.stamina -= down_value;

	if (current_status_.stamina < 0)
	{
		current_status_.stamina = 0;
		can_use_stamina_ = FALSE;
	}

	// スタミナ回復のタイマーを最初からスタート
	stamina_recovery_timer_->ReStart();
}

void StatusContainer::StaminaUp(const float up_value)
{
	current_status_.stamina += up_value;
	if (current_status_.stamina > base_status_.stamina)
	{
		current_status_.stamina = base_status_.stamina;
	}
}

void StatusContainer::StaminaUpMax()
{
	current_status_.stamina = base_status_.stamina;
	can_use_stamina_ = TRUE;
}

float StatusContainer::TakeDamage(float atk,AttackType type)
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
	// 受けたダメージの表示
	//printfDx("%.2f\n", damage);
	return damage;
}

void StatusContainer::TakeHeal(float heal)
{
	current_status_.hp += heal;

	if (current_status_.hp > base_status_.hp) { current_status_.hp = base_status_.hp; }
}

void StatusContainer::Activation(const std::string& name,std::shared_ptr<IPlayerUIGroup> player_ui_group)
{
	stat_modifire_group_->Activation(base_status_, current_status_, name,player_ui_group);
}

const Status StatusContainer::GetBaseStatus() const
{
	return base_status_;
}

const Status StatusContainer::GetCurrentStatus() const
{
	return current_status_;
}

const float StatusContainer::GetPhysicalATK() const
{
	// 現在の攻撃量
	auto current_physical_atk = current_status_.physical_atk;
	// ばらつきのある物理ダメージ
	float damage = GetNormalRandom(current_physical_atk, current_physical_atk * 0.3f);
	// clampする
	const float kMaxDamage = current_physical_atk + current_physical_atk * 0.3f;
	const float kMinDamage = current_physical_atk - current_physical_atk * 0.3f;
	damage = MyMath::Clamp(damage, kMinDamage, kMaxDamage);

	return damage;
}

const float StatusContainer::GetMagicATK() const
{
	// 
	float current_magic_atk = current_status_.magic_atk;
	
	// ばらつきのある魔法ダメージを
	float damage = GetNormalRandom(current_magic_atk, 10.f);
	// clampする
	const float kMaxDamage = current_magic_atk + current_magic_atk * 0.3f;
	const float kMinDamage = current_magic_atk - current_magic_atk * 0.3f;
	damage = MyMath::Clamp(damage, kMinDamage, kMaxDamage);
	return damage;
}

const bool StatusContainer::CanUseStamina() const
{
	return can_use_stamina_;
}

void StatusContainer::StaminaUpdate()
{
	// スタミナが使えないときはmaxになるまで使えない
	if (!can_use_stamina_)
	{
		current_status_.stamina += stamina_recovery_value_ * FPS::GetInstance().GetDeltaTime();
		if (StaminaRecovery())
		{
			// スタミナ使用を許可
			can_use_stamina_ = TRUE;
		}
		return;
	}

	// baseと一緒なら処理をしない
	if (current_status_.stamina == base_status_.stamina) { return; }
	// タイマーを加算
	stamina_recovery_timer_->Update();

	// タイマーが終わったら
	if (stamina_recovery_timer_->GetIsEnd())
	{
		current_status_.stamina += stamina_recovery_value_ * FPS::GetInstance().GetDeltaTime();
		// スタミナを回復する
		StaminaRecovery();
	}
}

bool StatusContainer::StaminaRecovery()
{
	// スタミナを回復する
	
	if (current_status_.stamina >= base_status_.stamina)
	{
		current_status_.stamina = base_status_.stamina;
		return TRUE;
	}
	return FALSE;
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

