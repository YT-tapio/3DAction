#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include<vector>
#include"DxLib.h"
#include"conbo_action.h"
#include"object_base.h"
#include"conbo.h"
#include"character_base.h"
#include"animator_base.h"

ConboAction::ConboAction(std::weak_ptr<ObjectBase>owner, std::unordered_map<int, std::shared_ptr<Conbo>> conbos)
	: BehaviorBase(owner)
	, conbos_(conbos)
	, current_conbo_(0)
	, go_next_(FALSE)
{

}

ConboAction::~ConboAction()
{

}

void ConboAction::Init()
{
	for (auto& conbo : conbos_)
	{
		conbo.second->Init();
	}
	current_conbo_ = 0;
	go_next_ = FALSE;
}

void ConboAction::Update()
{
	//go_nextされているときにanimationが

	//キャラクターなのが前提ではある
	auto character = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
	
	if (character == nullptr) { return; }
	if(CheckNextConbo(character))
	{
		conbos_[current_conbo_]->Exit();
		current_conbo_++;
		// キャラにanimationを再生させる
		character->GetAnimator()->PlayRequest(conbos_[current_conbo_]->GetMyAnimName());
		go_next_ = FALSE;
	}

	conbos_[current_conbo_]->Update();
}

void ConboAction::Exit()
{
	current_conbo_ = 0;
	go_next_ = FALSE;
}

void ConboAction::Draw()
{

}

void ConboAction::Debug()
{
	conbos_[current_conbo_]->Debug();
}

void ConboAction::GoNext()
{
	go_next_ = TRUE;
}


const bool ConboAction::CheckNextConboReady() const
{
	auto current_conbo = conbos_.find(current_conbo_);
	if (current_conbo == conbos_.end()) { return FALSE; }
	return current_conbo->second->CheckNextReady();
}

const bool ConboAction::CheckIsEnd() const
{
	auto conbo = conbos_.find(current_conbo_);
	if (conbo == conbos_.end()) { return FALSE; }
	if (!conbo->second->CheckIsEnd()) { return FALSE; }
	return TRUE;
}

const std::string ConboAction::GetFirstConboAnimation() const
{
	const int kFirstConbo = 0;
	const std::string kNothing = "nothing";
	auto conbo = conbos_.find(kFirstConbo);
	if (conbo == conbos_.end()) { return kNothing; }
	return conbo->second->GetMyAnimName();
}

const bool ConboAction::CheckNextConbo(std::shared_ptr<CharacterBase> character) const
{
	auto conbo = conbos_.find(current_conbo_);
	if (conbo == conbos_.end()) { return FALSE; }
	//自分の指定したanimationが次に移れるかの範囲内なのか
	if (!go_next_) { return FALSE; }
	if (!conbo->second->CheckAnimation()) { return FALSE; }
	return TRUE;
}