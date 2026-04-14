#include<memory>
#include"DxLib.h"
#include"punch.h"
#include"vector_assistant.h"
#include"object_base.h"
#include"physics.h"
#include"rigid_body.h"
#include"capsule.h"
#include"debug.h"
#include"enemy_base.h"
#include"player.h"
#include"object_base.h"
#include"animator_base.h"

Punch::Punch(std::weak_ptr<ObjectBase> owner, VECTOR* pos, 
	std::string my_anim_name, float min_coll_ratio, float max_coll_ratio, std::shared_ptr<RigidBody> body)
	: AttackBase(owner)
	, my_anim_name_(my_anim_name)
	, min_coll_ratio_(min_coll_ratio)
	, max_coll_ratio_(max_coll_ratio)
{
	pos_ = pos;
	rigid_body_ = body;
}

Punch::~Punch()
{

}

void Punch::Init()
{
	rigid_body_->Init(weak_from_this());
	Physics::GetInstance().AddBody(rigid_body_);
	rigid_body_->NotActive();
}

void Punch::Update()
{
	// ‚Ç‚¤‚µ‚æ‚¤
	// ³’¼¡‚±‚Ì’†‚Å‚Í‚½‚¾Žè‚É“–‚½‚è”»’è‚ðŽ‚½‚¹‚Ä‚¢‚é‚¾‚¯‚È‚ñ‚¾‚æ‚È
	// owner‚Épunch‚ð”­¶‚³‚¹‚½‚¢‚æ‚È
	rigid_body_->NotActive();
	auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());

	if (owner == nullptr) { return; }
	auto owner_animator = owner->GetAnimator();
	if (owner_animator == nullptr) { return; }
	// “–‚½‚è”»’è‚ð‚Ìactive‚ð‚µ‚Ü‚·
	
	float punch_play_time = owner_animator->GetRatio(my_anim_name_);
	//printfDx("%.2f\n", punch_play_time);
	if (punch_play_time > min_coll_ratio_ && punch_play_time < max_coll_ratio_) { rigid_body_->Active(); }

}

void Punch::Exit()
{
	rigid_body_->NotActive();
}

void Punch::Debug()
{
	rigid_body_->Debug();
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "-----AttackCollider----", GetColor(255, 255, 255));
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(*pos_);
}

void Punch::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{
	auto owner = owner_.lock();

	auto player_from_owner = std::dynamic_pointer_cast<Player>(owner);
	auto enemy_from_owner = std::dynamic_pointer_cast<EnemyBase>(owner);
	auto player = std::dynamic_pointer_cast<Player>(object);
	auto enemy = std::dynamic_pointer_cast<EnemyBase>(object);
	if (player == player_from_owner) { return; }

	//if (enemy != nullptr) { printfDx("enemy‚ª‚¢‚é‚¼‚¨‚¢"); return; }
	// if (player != nullptr) { printfDx("player‚ª‚¢‚é‚¼\n"); return; }

}