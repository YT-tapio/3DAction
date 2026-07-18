#include<memory>
#include"DxLib.h"
#include"active_stat_modifire.h"
#include"condition_timer.h"
#include"variable_timer.h"
#include"status.h"

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

void ActiveStatModifire::Activation(const Status& base_status, Status& current_status, const StatModifire& effecacy_data)
{
	// この瞬間に効果を発揮させる
	data_ = effecacy_data;

	switch (data_.category)
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

	// この瞬間にui描画させたいを行わせたい



	timer_->Stop();
	timer_->ChangeMaxTime(data_.time);
	timer_->ReStart();
	is_active_ = TRUE;
}

const bool ActiveStatModifire::GetIsActive() const
{
	return is_active_;
}

void ActiveStatModifire::Release(const Status& base_status, Status& current_status)
{
	switch (data_.category)
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