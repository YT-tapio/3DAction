#include<vector>
#include<memory>
#include"DxLib.h"
#include"object_base.h"
#include"check_my_area.h"
#include"area_heal_give_player.h"
#include"takable_heal_player_interface.h"

AreaHealGivePlayer::AreaHealGivePlayer(std::weak_ptr<ObjectBase> owner, std::shared_ptr<CheckMyArea> area, VECTOR* pos)
	: AreaHeal(owner,area,pos)
{

}

AreaHealGivePlayer::~AreaHealGivePlayer()
{

}

void AreaHealGivePlayer::Draw()
{

}

void AreaHealGivePlayer::Debug()
{
	my_area_->Debug();
}

void AreaHealGivePlayer::Action(std::shared_ptr<ObjectBase> object)
{
	// ƒq[ƒ‹‚ğó‚¯‚é‚à‚Ì‚È‚Ì‚©‚ğ”»•Ê‚ğ‚·‚é
	auto obj = std::dynamic_pointer_cast<ITakableHealPlayer>(object);
	if (obj == nullptr) { return; }

	obj->OnHealFromPlayer(1.f);
}