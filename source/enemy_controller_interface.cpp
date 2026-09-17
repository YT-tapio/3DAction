#include"DxLib.h"
#include"enemy_controller_interface.h"
#include"vector_assistant.h"
#include"enemy_observer_interface.h"

void IEnemyController::AddBossObserver(IEnemyObserver* observer)
{

}

const VECTOR IEnemyController::GetBossCenterPos() const
{
	return VectorAssistant::VGetZero();
}

const VECTOR IEnemyController::GetBossFrontDir() const
{
	return VectorAssistant::VGetZero();
}