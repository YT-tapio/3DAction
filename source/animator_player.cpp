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

AnimatorPlayer::AnimatorPlayer(int handle, std::string name)
	: AnimatorBase("player/" + name, handle)
{
	
}

AnimatorPlayer::~AnimatorPlayer()
{
	

}

void AnimatorPlayer::ChangeAnimation()
{
	before_anim_name_ = now_anim_name_;

	std::map<int, std::string, std::greater<int>> priority_request_name_mp;


	// キャンセルタイミング時にpriorityの低いものだった場合はかえてもok


	if (!request_names_.empty())
	{
		for (auto& request_name : request_names_)
		{
			int priority = animation_datas_[request_name].priority;
			priority_request_name_mp[priority] = request_name;
		}
	}
	// requestの中でもpriorityのたかいものを取る。
	if (!priority_request_name_mp.empty()) { now_anim_name_ = priority_request_name_mp.begin()->second; }
}