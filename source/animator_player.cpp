#include<memory>
#include<map>
#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"player.h"
#include"animator_base.h"
#include"animation_data.h"
#include"animator_player.h"
#include"load_animation.h"
#include"fps.h"
#include"rigid_body.h"
#include"physics_interface.h"

AnimatorPlayer::AnimatorPlayer(int handle, std::shared_ptr<Player> player, std::string name)
	: AnimatorBase("player/" + name, handle)
	, player_(player)
{
	
}

AnimatorPlayer::~AnimatorPlayer()
{
	

}

void AnimatorPlayer::ChangeAnimation()
{
	before_anim_name_ = now_anim_name_;

	std::map<int, std::string, std::greater<int>> request_name_priority_mp;
	if (player_->GetIsMove()) { PlayRequest(kJogging); }
	if (player_->GetIsDash()) { PlayRequest(kRun); }
	if (player_->GetOnGround()){ PlayRequest(kIdle); }

	if (!request_names_.empty())
	{
		for (auto& request_name : request_names_)
		{
			int priority = animation_datas_[request_name].priority;
			request_name_priority_mp[priority] = request_name;
		}
	}
	// request‚Ì’†‚Å‚àpriority‚Ì‚½‚©‚¢‚à‚Ì‚ðŽæ‚éB
	if (!request_name_priority_mp.empty()) { now_anim_name_ = request_name_priority_mp.begin()->second; }
}