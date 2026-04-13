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
{

}

ConboAction::~ConboAction()
{

}

void ConboAction::Init()
{
	current_conbo_ = 0;
}

void ConboAction::Update()
{

}

void ConboAction::Draw()
{

}

void ConboAction::Debug()
{

}
