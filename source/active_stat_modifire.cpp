#include<memory>
#include"DxLib.h"
#include"active_stat_modifire.h"
#include"condition_timer.h"
#include"variable_timer.h"
#include"status.h"
#include"player_ui_group_interface.h"

ActiveStatModifire::ActiveStatModifire()
	: timer_(std::make_shared<VariableTimer>())
	, data_{}
	, is_active_(FALSE)
{

}

ActiveStatModifire::~ActiveStatModifire()
{

}

void ActiveStatModifire::Init()
{
	is_active_ = FALSE;
	timer_->Init();
}

void ActiveStatModifire::Update(const Status& base_status,Status& current_status)
{
	// 効果量
	timer_->Update();

	// タイマーが終了したらバフの解除
	if (timer_->GetIsEnd())
	{
		// バフの解除
		Release(base_status,current_status);
		is_active_ = FALSE;
	}
}

void ActiveStatModifire::Activation(const Status& base_status, Status& current_status, const StatModifire& stat_modifire,std::shared_ptr<IPlayerUIGroup> player_ui_group)
{
	// この瞬間に効果を発揮させる
	data_ = stat_modifire;

	switch (data_.type)
	{
	case StatType::kPhysicalATK:
		current_status.physical_atk += base_status.physical_atk * data_.rate;
		break;

	case StatType::kPhysicalDEF:
		current_status.physical_def += base_status.physical_def * data_.rate;
		break;

	case StatType::kMagicATK:
		current_status.magic_atk += base_status.magic_atk * data_.rate;
		break;

	case StatType::kMagicDEF:
		current_status.magic_def += base_status.magic_def * data_.rate;
		break;

	default:
		printfDx("そのカテゴリはないです\n");
		break;
	}

	

	timer_->Stop();
	timer_->ChangeMaxTime(data_.time);
	timer_->ReStart();
	is_active_ = TRUE;

	std::function<bool()> end_condition = [this]() -> bool
		{
			return timer_->GetIsEnd();
		};

	// この瞬間にui描画させたい
	player_ui_group->SpawnStatModifire(end_condition, data_.type, data_.operation);

}

const bool ActiveStatModifire::GetIsActive() const
{
	return is_active_;
}

void ActiveStatModifire::Release(const Status& base_status, Status& current_status)
{
	switch (data_.type)
	{
	case StatType::kPhysicalATK:
		current_status.physical_atk -= base_status.physical_atk * data_.rate;
		break;

	case StatType::kPhysicalDEF:
		current_status.physical_def -= base_status.physical_def * data_.rate;
		break;

	case StatType::kMagicATK:
		current_status.magic_atk -= base_status.magic_atk * data_.rate;
		break;

	case StatType::kMagicDEF:
		current_status.magic_def -= base_status.magic_def * data_.rate;
		break;

	default:
		break;
	}
}