#include<memory>
#include<string>
#include<unordered_map>
#include"enemy_cool_time_controller.h"


EnemyCoolTimeController::EnemyCoolTimeController()
{

}

EnemyCoolTimeController::~EnemyCoolTimeController()
{

}

void EnemyCoolTimeController::AddCoolTime(const std::string& name,const float& time)
{
	cool_times_[name] = std::make_shared<ConditionTimer>(time);
	cool_times_[name]->Init();
	cool_times_[name]->Max();
}

void EnemyCoolTimeController::Init()
{
	for (auto& cool_time : cool_times_)
	{
		cool_time.second->Init();
		cool_time.second->Max();
	}
}

void EnemyCoolTimeController::Update()
{
	for (auto& cool_time : cool_times_)
	{
		cool_time.second->Update();
	}
}

void EnemyCoolTimeController::Start(const std::string& name)
{
	auto cool_time = cool_times_.find(name);
	if (cool_time == cool_times_.end()) { return; }
	cool_time->second->ReStart();
}

const bool EnemyCoolTimeController::GetIsEnd(const std::string& name) const
{
	auto cool_time = cool_times_.find(name);
	if (cool_time == cool_times_.end()) { return false; }

	return cool_time->second->GetIsEnd();
}