#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include<vector>
#include"DxLib.h"
#include"conbo_action.h"
#include"object_base.h"
#include"conbo.h"

ConboAction::ConboAction(std::weak_ptr<ObjectBase>owner, std::unordered_map<int, std::shared_ptr<Conbo>> conbos)
	: BehaviorBase(owner)
	, conbos_(conbos)
	, current_conbo_(0)
	, go_next_(FALSE)
	, is_active_(FALSE)
{

}

ConboAction::~ConboAction()
{

}

void ConboAction::Init()
{
	current_conbo_ = 0;
	go_next_ = FALSE;
}

void ConboAction::Update()
{
	conbos_[current_conbo_]->Update();
}

void ConboAction::Draw()
{

}

void ConboAction::Debug()
{

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