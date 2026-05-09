#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include<vector>
#include"DxLib.h"
#include"combo_action.h"
#include"object_base.h"
#include"combo.h"
#include"character_base.h"
#include"animator_base.h"
#include"behavior_status.h"

ComboAction::ComboAction(std::weak_ptr<ObjectBase>owner, std::unordered_map<int, std::shared_ptr<Combo>> combos)
	: BehaviorBase(owner)
	, combos_(combos)
	, current_combo_(0)
	, go_next_(FALSE)
	, is_change_(FALSE)
{

}

ComboAction::~ComboAction()
{

}

void ComboAction::Init()
{
	for (auto& combo : combos_)
	{
		combo.second->Init();
	}
	current_combo_ = 0;
	go_next_ = FALSE;
}

BehaviorStatus ComboAction::Update()
{
	//go_nextされているときにanimationが

	//キャラクターなのが前提ではある
	auto character = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
	is_change_ = FALSE;
	if (character == nullptr) { return BehaviorStatus::kFailure; }
	if(CheckNextcombo(character))
	{
		combos_[current_combo_]->Exit();
		current_combo_++;
		// キャラにanimationを再生させる
		character->GetAnimator()->PlayRequest(combos_[current_combo_]->GetMyAnimName());
		go_next_ = FALSE;
		is_change_ = TRUE;
	}

	return combos_[current_combo_]->Update();
}

void ComboAction::Exit()
{
	current_combo_ = 0;
	go_next_ = FALSE;
}

void ComboAction::Draw()
{

}

void ComboAction::Debug()
{
	combos_[current_combo_]->Debug();
}

void ComboAction::GoNext()
{
	go_next_ = TRUE;
}

const int ComboAction::GetCurrentcombo() const
{
	return current_combo_;
}

const bool ComboAction::CheckNextcomboReady() const
{
	auto current_combo = combos_.find(current_combo_);
	if (current_combo == combos_.end()) { return FALSE; }
	return current_combo->second->CheckNextReady();
}

const bool ComboAction::CheckIsEnd() const
{
	auto combo = combos_.find(current_combo_);
	if (combo == combos_.end()) { return FALSE; }
	if (!combo->second->CheckIsEnd()) { return FALSE; }
	return TRUE;
}

const bool ComboAction::CheckChangecombo() const
{
	return is_change_;
}

const std::string ComboAction::GetFirstcomboAnimation() const
{
	const int kFirstcombo = 0;
	const std::string kNothing = "nothing";
	auto combo = combos_.find(kFirstcombo);
	if (combo == combos_.end()) { return kNothing; }
	return combo->second->GetMyAnimName();
}

const bool ComboAction::CheckNextcombo(std::shared_ptr<CharacterBase> character) const
{
	auto combo = combos_.find(current_combo_);
	if (combo == combos_.end()) { return FALSE; }
	//自分の指定したanimationが次に移れるかの範囲内なのか
	if (!go_next_) { return FALSE; }
	if (!combo->second->CheckAnimation()) { return FALSE; }
	return TRUE;
}